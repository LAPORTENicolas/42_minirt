/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:21:05 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/21 15:53:52 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <limits.h>
#include <float.h>
#include <math.h>

void	calc_abc_cone(t_ray ray, float *val, float k)
{
	val[0] = ray.dir_loc.x * ray.dir_loc.x \
		+ ray.dir_loc.z * ray.dir_loc.z \
		- (ray.dir_loc.y * ray.dir_loc.y * k);
	val[1] = 2 * (ray.origin_loc.x * ray.dir_loc.x \
		+ ray.origin_loc.z * ray.dir_loc.z \
		- ray.origin_loc.y * ray.dir_loc.y * k);
	val[2] = ray.origin_loc.x * ray.origin_loc.x \
		+ ray.origin_loc.z * ray.origin_loc.z \
		- (ray.origin_loc.y * ray.origin_loc.y * k);
}

float	cone_height(t_ray ray, t_cone *cone, float t)
{
	t_vec3	p;
	float	h;

	p = vec_add(ray.origin_loc, vec_mul(ray.dir_loc, t));
	h = p.y;
	if (h < 0.0f || h > cone->height)
		return (-1);
	return (t);
}

float	cone_t_world(t_cone *cone, t_ray ray, float t)
{
	t_vec3	p_local;
	t_vec3	p_world;
	float	t_world;

	p_local = vec_add(ray.origin_loc, vec_mul(ray.dir_loc, t));
	p_world = vec_add(quat_rotate_vec(cone->q, p_local), cone->pos);
	t_world = vec_length(vec_sub(p_world, ray.origin));
	return (t_world);
}
