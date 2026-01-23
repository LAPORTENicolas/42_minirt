/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:28:12 by jodde             #+#    #+#             */
/*   Updated: 2026/01/15 18:08:06 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <limits.h>
#include <math.h>
#include <pthread.h>
#include <float.h>
#include <stdio.h>

/// @brief 
/// Fonction qui calcule les trois composantes 
/// du rayon en fonction du pixel visé (x, y)
/// @param env 
/// @param x 
/// @param y 
/// @return 

t_ray	gen_world_ray(t_env *env, float x, float y)
{
	t_ray	r;
	float	aspect_ratio;
	float	fov_rad;
	float	scale;

	ft_memset(&r, 0, sizeof(t_ray));
	aspect_ratio = (float)env->win.width / (float)env->win.height;
	fov_rad = calc_rad (env->camera.fov);
	scale = tanf(fov_rad / 2.0f);
	r.dir = normalize(vec_add(vec_add(env->camera.forward, \
	vec_mul(env->camera.right, x * scale)), vec_mul(env->camera.up, \
	y * scale / aspect_ratio)));
	r.origin = env->camera.pos;
	return (r);
}

void	gen_local_ray(t_ray *ray, t_quat object_q, t_vec3 object_pos)
{
	t_quat	qi;

	qi = q_conj(object_q);
	ray->origin_loc = quat_rotate_vec(qi, vec_sub(ray->origin, object_pos));
	ray->dir_loc = normalize(quat_rotate_vec(qi, ray->dir));
	ray->dir_loc = normalize(ray->dir_loc);
}
