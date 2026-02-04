/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:28:39 by jodde             #+#    #+#             */
/*   Updated: 2026/02/04 20:07:06 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../lib/libft/libft.h"
#include <stdio.h>
#include <math.h>
#include <pthread.h>

int	init_env(t_env *env, char *str)
{
	ft_memset(env, 0, sizeof(t_env));
	if (!ft_strrchr(str, '.') || ft_strncmp(ft_strrchr(str, '.'), ".rt", 3))
	{
		printf("Error: Bad file scene need .rt %s\n", ft_strchr(str, '.'));
		return (1);
	}
	env->file = ft_strndup(str, ft_strlen(str));
	if (!env->file)
		return (1);
	env->win.need_reset = 1;
	return (0);
}
void	init_mutexes(t_env *env)
{
    pthread_mutex_init(&env->reset_mutex, NULL);
    pthread_mutex_init(&env->done_mutex, NULL);
    pthread_cond_init(&env->reset_cond, NULL);
    pthread_cond_init(&env->done_cond, NULL);
}

void	init_threads(t_env *env)
{
    int	i;
	int	core;

	i = 0;
	env->size = env->win.width * env->win.height;
	core = sysconf(_SC_NPROCESSORS_ONLN);
	env->nb_threads = fmin(core, MAX_THREAD);
	if (env->nb_threads <= 0)
		env->nb_threads = 1;
	if (env->nb_threads > env->size)
		env->nb_threads = env->size;
	env->threads = malloc(sizeof(t_task) * env->nb_threads);
	if (!env->threads)
		exit_mlx(env);
	while (i < env->nb_threads)
	{
		ft_memset(&env->threads[i], 0, sizeof(t_task));
		env->threads[i].env = env;
		i++;
	}
}

int	init_tasks(t_env *env)
{
	init_threads(env);
    init_mutexes(env);
    if (create_threads(env->threads, env->nb_threads, env->size) != 0)
	{
		free(env->threads);
		env->threads = NULL;
		return(1);
	}
	return(0);
}