/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:36:34 by jodde             #+#    #+#             */
/*   Updated: 2026/02/04 20:45:50 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>


void	join_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_threads)
		pthread_join(env->threads[i++].th_ray, NULL);
	pthread_mutex_destroy(&env->reset_mutex);
	pthread_mutex_destroy(&env->done_mutex);
	pthread_cond_destroy(&env->reset_cond);
	pthread_cond_destroy(&env->done_cond);
}

void	*thread_routine(void *arg)
{
	t_task	*task;
	t_env	*env;

	task = (t_task *)arg;
	env = task->env;
	while (1)
	{
		pthread_mutex_lock(&env->reset_mutex);
		while (env->reset == 0)
			pthread_cond_wait(&env->reset_cond, &env->reset_mutex);
		pthread_mutex_unlock(&env->reset_mutex);
		execute_thread(task);
		pthread_mutex_lock(&env->done_mutex);
		env->threads_done++;
		if (env->threads_done == env->nb_threads)
    		pthread_cond_signal(&env->done_cond);
		pthread_mutex_unlock(&env->done_mutex);
	}
	return (NULL);
}

int	create_threads(t_task *threads, int nb_threads, int size)
{
	int	i;
	int	chunk;

	i = 0;
	chunk = size / nb_threads;
	while (i < nb_threads)
	{
		threads[i].start = i * chunk;
		if (i == nb_threads - 1)
			threads[i].end = size;
		else
			threads[i].end = threads[i].start + chunk;
		if (pthread_create(&threads[i].th_ray, NULL, thread_routine, &threads[i]) != 0)
		{
			printf("Failed to create thread");
			while (--i >= 0)
				pthread_join(threads[i].th_ray, NULL);
			return (1);
		}
		i++;
	}
	return (0);
}

