/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:30:35 by jodde             #+#    #+#             */
/*   Updated: 2026/02/05 11:18:40 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>
#include <limits.h>
#include <float.h>

float	hit_cylinder_top(t_ray ray, t_cylinder *cyl)
{
	float	t;
	float	x;
	float	y;

	if (fabsf(ray.dir_loc.y) < EPS)
		return (-1.0f);
	t = (cyl->height - ray.origin_loc.y) / ray.dir_loc.y;
	if (t < 0.001f)
		return (-1);
	x = ray.origin_loc.x + t * ray.dir_loc.x;
	y = ray.origin_loc.z + t * ray.dir_loc.z;
	if ((x * x + y * y) <= cyl->r * cyl->r)
		return (t);
	return (-1);
}

float	hit_cylinder_bottom(t_ray ray, t_cylinder *cyl)
{
	float	t;
	float	x;
	float	y;

	if (fabsf(ray.dir_loc.y) < EPS)
		return (-1.0f);
	t = (0.0f - ray.origin_loc.y) / ray.dir_loc.y;
	if (t < 0.001f)
		return (-1);
	x = ray.origin_loc.x + t * ray.dir_loc.x;
	y = ray.origin_loc.z + t * ray.dir_loc.z;
	if ((x * x + y * y) <= cyl->r * cyl->r)
		return (t);
	return (-1);
}

/* 
 * formule d intersction avec un cylindre: P(t) = O + tD, 
 * avec en repere local: O = ray.origin_loc et D = ray.dir_loc
 */
float	hit_cylinder_side(t_ray ray, t_cylinder *cyl)
{
	float	val[3];
	float	disc;
	float	t[2];
	float	best;

	best = FLT_MAX;
	val[0] = ray.dir_loc.x * ray.dir_loc.x + ray.dir_loc.z * ray.dir_loc.z;
	val[1] = 2.0f * (ray.origin_loc.x * ray.dir_loc.x + \
			ray.origin_loc.z * ray.dir_loc.z);
	val[2] = ray.origin_loc.x * ray.origin_loc.x + ray.origin_loc.z * \
		ray.origin_loc.z - cyl->r * cyl->r;
	disc = val[1] * val[1] - 4 * val[0] * val[2];
	if (disc < 0.0f || fabsf(val[0]) < EPS)
		return (-1);
	if (disc < EPS)
		disc = 0.0f;
	t[0] = (-val[1] - sqrtf(disc)) / (2 * val[0]);
	if (t[0] > EPS && cylinder_height(ray, cyl, t[0]) > 0)
		best = t[0];
	t[1] = (-val[1] + sqrtf(disc)) / (2 * val[0]);
	if (t[1] > EPS && cylinder_height(ray, cyl, t[1]) > 0)
		best = fminf(best, t[1]);
	if (best < FLT_MAX)
		return (best);
	return (-1.0f);
}

float	hit_cylinder(t_ray ray, t_cylinder *cyl)
{
	float	t;
	float	t_min;

	t_min = FLT_MAX;
	t = hit_cylinder_side(ray, cyl);
	if (t > EPS && t < t_min)
	{
		t_min = t;
		cyl->hit_type = 0;
	}
	t = hit_cylinder_top(ray, cyl);
	if (t > EPS && t < t_min)
	{
		t_min = t;
		cyl->hit_type = 1;
	}
	t = hit_cylinder_bottom(ray, cyl);
	if (t > EPS && t < t_min)
	{
		t_min = t;
		cyl->hit_type = 2;
	}
	return (t_min);
}

t_ray_d	check_all_cylinders(t_env *env, t_ray ray, \
		t_cylinder *last, int light)
{
	t_cylinder	*cy;
	t_list		*cylinders;
	t_ray_d		r;
	float		t_tmp;

	ft_memset(&r, 0, sizeof(t_ray_d));
	r.t = FLT_MAX;
	if (!env->scene.cylinders)
		return (r);
	cylinders = env->scene.cylinders;
	while (cylinders)
	{
		cy = cylinders->content;
		gen_local_ray(&ray, cy->q, cy->pos);
		t_tmp = hit_cylinder(ray, cy);
		if (t_tmp > 0 && t_tmp < r.t && \
				cy != last && !(light && cy->glass_flag))
		{
			r.t = cyl_t_world(cy, ray, &r.hp_loc, t_tmp);
			r.ray = ray;
			set_cyl_data(&r, cy, t_tmp);
		}
		cylinders = cylinders->next;
	}
	return (r);
}
