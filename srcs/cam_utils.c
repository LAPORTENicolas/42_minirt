/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:10:18 by jodde             #+#    #+#             */
/*   Updated: 2026/01/21 16:16:24 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h>

void	define_worldup(t_vec3 *world_up, t_vec3 forward)
{
	t_vec3	c;

	world_up->x = 0;
	world_up->y = 1;
	world_up->z = 0;
	c = vec_cross(*world_up, forward);
	if (fabs(c.x) < EPS && fabs(c.y) < EPS && \
			fabs(c.z) < EPS)
	{
		world_up->x = 0;
		world_up->y = 0;
		world_up->z = 1;
	}
}

void	copy_origin_cam(t_env *env)
{
	env->origin.pos.x = env->camera.pos.x;
	env->origin.pos.y = env->camera.pos.y;
	env->origin.pos.z = env->camera.pos.z;
	env->origin.forward.x = env->camera.forward.x;
	env->origin.forward.y = env->camera.forward.y;
	env->origin.forward.z = env->camera.forward.z;
	env->origin.world_up.x = env->camera.world_up.x;
	env->origin.world_up.y = env->camera.world_up.y;
	env->origin.world_up.z = env->camera.world_up.z;
	env->origin.right.x = env->camera.right.x;
	env->origin.right.y = env->camera.right.y;
	env->origin.right.z = env->camera.right.z;
	env->origin.up.x = env->camera.up.x;
	env->origin.up.y = env->camera.up.y;
	env->origin.up.z = env->camera.up.z;
	env->origin.fov = env->camera.fov;
}

void	restore_origin_cam(t_env *env)
{
	env->camera.pos = env->origin.pos;
	env->camera.forward = env->origin.forward;
	env->camera.right = env->origin.right;
	env->camera.up = env->origin.up;
	env->camera.fov = env->origin.fov;
	define_worldup(&env->camera.world_up, env->camera.forward);
	env->camera.right = normalize(vec_cross(env->camera.world_up, \
		env->camera.forward));
	env->camera.up = normalize(vec_cross(env->camera.forward, \
		env->camera.right));
}
