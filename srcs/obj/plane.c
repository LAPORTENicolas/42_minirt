/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:37:25 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/21 21:22:34 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdint.h>

/**
 * @brief check_plane_hit
 *
 * Retourne la distance de l'intersection
 * la plus proche pour un plan et un rayon
 * ou -1 si pas d'intersection
 *
 * @param t_ray ray
 * @param t_plane *object
 */
float	check_plane_hit(t_ray ray)
{
	float	t;

	if (fabs(ray.dir_loc.y) < EPS)
		return (-1);
	t = -ray.origin_loc.y / ray.dir_loc.y;
	if (t > 0)
		return (t * .99);
	return (-1);
}

/**
 * @brief set_plane_data
 *
 * Definit les valeurs pour un plan dans *r
 *
 * @param t_ray_d *r 
 * @param t_ray ray 
 * @param t_plane plane 
 * @param float t 
 *
 * @return void
 */
void	set_plane_data(t_ray_d *r, t_ray ray, t_plane *p, float t)
{
	t_vec3	uv;
	t_vec3	local_n;
	float	dot;

	local_n = (t_vec3){0, 1, 0};
	uv = (t_vec3){0, 0, 0};
	r->ray = ray;
	r->t = plane_t_world(p, ray, t);
	r->t2 = r->t;
	r->color = p->color;
	r->n = normalize(quat_rotate_vec(p->q, local_n));
	dot = vec_dot(r->n, r->ray.dir);
	if (dot > 0)
		r->n = vec_mul(r->n, -1);
	r->obj = p;
	r->hp = vec_add(ray.origin, vec_mul(ray.dir, t));
	r->reflection = .2;
	r->roughness = .3;
	r->type = PLANE;
	r->glass_flag = p->glass_flag;
	if (p->texture || p->checkboard_flag || p->pal_flag)
		manage_texture_plane(uv, r, p);
}

/**
 * @brief check_all_planes
 *
 * Verifie s'il y a une intersection sur 
 * tous les plans
 *
 * @param t_ray ray
 * @param t_list *planes
 *
 * @return t_ray_d
 */
t_ray_d	check_all_planes(t_ray ray, t_list *planes, t_plane *last, int light)
{
	t_ray_d		r;
	t_plane		*p;
	float		tmp;

	ft_memset(&r, 0, sizeof(t_ray_d));
	r.t = FLT_MAX;
	while (planes)
	{
		p = planes->content;
		gen_local_ray(&ray, p->q, p->pos);
		tmp = check_plane_hit(ray);
		if (tmp < r.t && tmp != -1 && r.t > 0 \
				&& p != last && !(light && p->glass_flag))
			set_plane_data(&r, ray, p, tmp);
		planes = planes->next;
	}
	return (r);
}
