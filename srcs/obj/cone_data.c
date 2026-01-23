/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 13:21:05 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/23 12:34:30 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <limits.h>
#include <float.h>
#include <math.h>

t_vec3	cone_normal_local(t_cone *co, t_vec3 p_local)
{
	t_vec3	gradient;

	gradient.x = 2 * p_local.x;
	gradient.y = -2 * p_local.y * co->k;
	gradient.z = 2 * p_local.z;
	if (co->hit_type == 0)
		return (normalize(gradient));
	return ((t_vec3){0.0f, -1.0f, 0.0f});
}

void	cone_hp_n(t_cone *co, t_ray_d *r, float t)
{
	t_vec3	n_local;

	r->hp_loc = vec_add(r->ray.origin_loc, \
			vec_mul(r->ray.dir_loc, t));
	n_local = cone_normal_local(co, r->hp_loc);
	r->hp = vec_add(quat_rotate_vec(co->q, r->hp_loc), co->pos);
	r->n = normalize(quat_rotate_vec(co->q, n_local));
	if (vec_dot(r->n, r->ray.dir) > 0.0f)
		r->n = vec_mul(r->n, -1.0f);
}

void	set_cone_data(t_ray_d *r, t_cone *cone, float t)
{
	cone_hp_n(cone, r, t);
	r->color = cone->color;
	r->obj = cone;
	r->type = CONE;
	r->roughness = 0.0f;
	r->reflection = 0.1f;
	r->glass_flag = cone->glass_flag;
	if (cone->texture || cone->checkboard_flag || cone->pal_flag)
		manage_cone_texture(r, cone);
}
