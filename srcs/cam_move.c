/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:09:56 by jodde             #+#    #+#             */
/*   Updated: 2026/01/14 17:00:18 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h>

void	zoom_in(t_cam *camera)
{
	camera->pos = vec_add(camera->pos, vec_mul(camera->forward, ZOOM_STEP));
}

void	zoom_out(t_cam *camera)
{
	camera->pos = vec_sub(camera->pos, vec_mul(camera->forward, ZOOM_STEP));
}

void	rotate_camera(t_cam *camera, int dx, int dy)
{
	camera->yaw -= dx * ROT_SENS;
	camera->pitch += dy * ROT_SENS;
	if (camera->pitch > 89.0f)
		camera->pitch = 89.0f;
	if (camera->pitch < -89.0f)
		camera->pitch = -89.0f;
	camera->forward.x = cosf(calc_rad(camera->pitch)) \
				* sinf(calc_rad(camera->yaw));
	camera->forward.y = sinf(calc_rad(camera->pitch));
	camera->forward.z = cosf(calc_rad(camera->pitch)) \
				* cosf(calc_rad(camera->yaw));
	camera->forward = normalize(camera->forward);
	define_worldup(&camera->world_up, camera->forward);
	camera->right = normalize(vec_cross(camera->world_up, camera->forward));
	camera->up = vec_cross(camera->forward, camera->right);
}

void	keyboard_move_camera(int key, t_env *env)
{
	if (key == Z_KEY)
	{
		env->z_key_pressed = 1;
		return ;
	}
	else if (key == W_KEY)
		env->camera.pos = vec_add(env->camera.pos, env->camera.up);
	else if (key == S_KEY)
		env->camera.pos = vec_sub(env->camera.pos, env->camera.up);
	else if (key == D_KEY)
		env->camera.pos = vec_add(env->camera.pos, env->camera.right);
	else if (key == A_KEY)
		env->camera.pos = vec_sub(env->camera.pos, env->camera.right);
	else
		return ;
	env->win.need_reset = 1;
}
