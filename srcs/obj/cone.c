/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:21:05 by nlaporte          #+#    #+#             */
/*   Updated: 2026/02/04 22:23:45 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

float	hit_cone_bottom(t_ray ray, t_cone *cone)
{
	float	t;
	float	x;
	float	y;

	if (fabsf(ray.dir_loc.y) < EPS)
		return (-1.0f);
	t = (cone->height - ray.origin_loc.y) / ray.dir_loc.y;
	if (t < EPS)
		return (-1);
	x = ray.origin_loc.x + t * ray.dir_loc.x;
	y = ray.origin_loc.z + t * ray.dir_loc.z;
	if ((x * x + y * y) <= cone->r * cone->r)
		return (t);
	return (-1);
}

float	hit_cone_side(t_ray ray, t_cone *cone)
{
	float	val[3];
	float	t[2];
	float	best;
	float	disc;
	float	k;

	ft_memset(&val, 0, sizeof(float) * 3);
	best = FLT_MAX;
	k = cone->k;
	calc_abc_cone(ray, val, k);
	disc = val[1] * val[1] - 4 * val[0] * val[2];
	if (disc < 0.0f || fabsf(val[0]) < EPS)
		return (-1.0f);
	if (disc < EPS)
		disc = 0.0f;
	t[0] = (-val[1] - sqrtf(disc)) / (2 * val[0]);
	if (t[0] > EPS && cone_height(ray, cone, t[0]) > 0)
		best = t[0];
	t[1] = (-val[1] + sqrtf(disc)) / (2 * val[0]);
	if (t[1] > EPS && cone_height(ray, cone, t[1]) > 0)
		best = fminf(best, t[1]);
	if (best < FLT_MAX)
		return (best);
	return (-1.0f);
}

float	check_cone(t_ray ray, t_cone *co)
{
	float	t;
	float	t_min;

	co->hit_type = 0;
	t_min = FLT_MAX;
	t = hit_cone_side(ray, co);
	if (t > EPS && t < t_min)
	{
		t_min = t;
		co->hit_type = 0;
	}
	t = hit_cone_bottom(ray, co);
	if (t > EPS && t < t_min)
	{
		t_min = t;
		co->hit_type = 1;
	}
	return (t_min);
}

t_ray_d	check_all_cones(t_env *env, t_ray ray, t_cone *last, int light)
{
	t_cone	*cone;
	t_list	*cones;
	t_ray_d	r;
	float	t_tmp;

	ft_memset(&r, 0, sizeof(t_ray_d));
	r.t = FLT_MAX;
	if (!env->scene.cones)
		return (r);
	cones = env->scene.cones;
	while (cones)
	{
		cone = cones->content;
		gen_local_ray(&ray, cone->q, cone->pos);
		t_tmp = check_cone(ray, cone);
		if (t_tmp > EPS && t_tmp < r.t && cone != last && \
			!(light && cone->glass_flag))
		{
			r.t = cone_t_world(cone, ray, t_tmp);
			r.ray = ray;
			set_cone_data(&r, cone, t_tmp);
		}
		cones = cones->next;
	}
	return (r);
}
