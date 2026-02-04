/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 17:36:18 by nlaporte          #+#    #+#             */
/*   Updated: 2026/02/04 23:26:46 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../lib/mlx/mlx.h"
#include <limits.h>
#include <pthread.h>
#include <stdio.h>
#include <float.h>

void	put_screen_mode_info(t_env *env)
{
	char	*mode;

	mode = NULL;
	if (env->screen_mode == CAMERA_MODE)
		mode = "CAMERA MODE";
	else
	{
		if (env->selected_obj == NO_OBJ)
			mode = "EDIT MODE - No Object Selected";
		else if (env->selected_obj == SPHERE_OBJ)
			mode = "EDIT MODE - Sphere Selected";
		else if (env->selected_obj == PLANE_OBJ)
			mode = "EDIT MODE - Plane Selected";
		else if (env->selected_obj == CYLINDER_OBJ)
			mode = "EDIT MODE - Cylinder Selected";
		else if (env->selected_obj == CONE_OBJ)
			mode = "EDIT MODE - Cone Selected";
		else if (env->selected_obj == LIGHT_OBJ)
			mode = "EDIT MODE - Light selection";
	}
	mlx_string_put(env->mlx, env->win.win, 10, 10, 0xFFFFFF, mode);
}

void	submit_task(t_env *env)
{
	pthread_mutex_lock(&env->reset_mutex);
	env->reset = 1;
	pthread_cond_broadcast(&env->reset_cond);
	pthread_mutex_unlock(&env->reset_mutex);
	pthread_mutex_lock(&env->done_mutex);
	while (env->threads_done < env->nb_threads)
		pthread_cond_wait(&env->done_cond, &env->done_mutex);
	env->threads_done = 0;
	pthread_mutex_unlock(&env->done_mutex);
	pthread_mutex_lock(&env->reset_mutex);
	env->reset = 0;
	pthread_mutex_unlock(&env->reset_mutex);
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

void	get_litle_resolution(t_env *env)
{
	if (env->litle_resolution)
	{
		env->win.width = WIDTH / SCALE;
		env->win.height = WIDTH / SCALE;
		env->size = (WIDTH / SCALE) * (HEIGHT / SCALE);
	}
	else
	{
		env->win.width = WIDTH;
		env->win.height = WIDTH;
		env->size = WIDTH * HEIGHT;
	}
}

void	render(t_env *env)
{
	if (env->win.need_reset)
	{
		reset_img_buf(env);
		env->win.count = 1;
		env->win.need_reset = 0;
		return ;
	}
	get_litle_resolution(env);
	submit_task(env);
	put_pixel_in_render(env);
	put_buffer_to_mlx(&env->win, env->win.count);
	if (EXP_RENDER)
	{
		if (env->win.count < FRAME_TARGET)
			printf("Render %i / %i\n", env->win.count, FRAME_TARGET);
		else
			return (make_screen_shoot(env), exit_mlx(env));
	}
	else
		mlx_put_image_to_window(env->mlx, env->win.win, env->win.img, 0, 0);
	env->win.count++;
	put_screen_mode_info(env);
}
