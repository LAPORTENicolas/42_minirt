/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:36:34 by jodde             #+#    #+#             */
/*   Updated: 2026/02/06 08:25:16 by jodde            ###   ########.fr       */
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
	pthread_mutex_destroy(&env->stop_mutex);
	pthread_mutex_destroy(&env->win_mutex);
	pthread_cond_destroy(&env->reset_cond);
	pthread_cond_destroy(&env->done_cond);
}

void	execute_thread(t_task *task)
{
	int		i;
	float	x;
	float	y;
	t_ray	ray;
	t_vec3	color;

	x = 0;
	y = 0;
	i = task->start;
	while (i < task->end)
	{
		ft_bzero(&ray, sizeof(t_ray));
		coordinate_from_index(task->env, i, &x, &y);
		ray = gen_world_ray(task->env, x, y);
		color = render_one_pixel(task->env, ray);
		put_pixel(task->env, color, i);
		i++;
	}
}

void	*thread_routine(void *arg)
{
	t_task	*task;

	task = (t_task *)arg;
	while (1)
	{
		pthread_mutex_lock(&task->env->stop_mutex);
		if (task->env->stop_render)
		{
			pthread_mutex_unlock(&task->env->stop_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&task->env->stop_mutex);
		pthread_mutex_lock(&task->env->reset_mutex);
		while (task->env->reset == 0)
			pthread_cond_wait(&task->env->reset_cond, &task->env->reset_mutex);
		pthread_mutex_unlock(&task->env->reset_mutex);
		execute_thread(task);
		pthread_mutex_lock(&task->env->done_mutex);
		task->env->threads_done++;
		if (task->env->threads_done == task->env->nb_threads)
			pthread_cond_signal(&task->env->done_cond);
		pthread_mutex_unlock(&task->env->done_mutex);
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
		if (pthread_create(&threads[i].th_ray, NULL, thread_routine, \
			&threads[i]) != 0)
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
