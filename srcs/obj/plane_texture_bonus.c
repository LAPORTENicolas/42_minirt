/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:37:25 by nlaporte          #+#    #+#             */
/*   Updated: 2026/02/04 20:05:13 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <limits.h>
#include <float.h>
#include <math.h>
#include <stdint.h>

/**
 * @brief get_plan_uv
 *
 * @param t_ray_d *ray 
 *
 * @return t_vec3 local coord plane
 */
t_vec3	get_plan_uv(t_ray_d *ray)
{
	t_vec3	hp_local;
	t_vec3	uv;
	t_plane	*p;

	p = (t_plane *)ray->obj;
	hp_local = quat_rotate_vec(q_conj(p->q), \
			vec_sub(ray->hp, p->pos));
	uv.x = hp_local.x;
	uv.y = hp_local.z;
	return ((t_vec3){uv.x, uv.y, 0});
}

void	plane_checkerboard(t_vec3 uv, t_ray_d *r)
{
	long	x;
	long	y;

	x = uv.x + INT_DIV2;
	y = uv.y + INT_DIV2;
	if ((x + y) % 2)
		r->color = (t_vec3){255, 255, 255};
	else
		r->color = (t_vec3){0, 0, 0};
	return ;
}

void	manage_texture_plane(t_vec3 uv, t_ray_d *r, t_plane *p)
{
	uv = get_plan_uv(r);
	if (p->checkboard_flag)
		return (plane_checkerboard(uv, r));
	if (p->pal_flag)
	{
		p->color = vec_mul(p->pal(uv.x * uv.y * 4), 255);
		return ;
	}
	pthread_mutex_lock(&p->texture->text_mutex);
	r->reflection = p->texture->reflection;
	r->roughness = p->texture->rougness;
	uv.x = uv.x * .1 - floor(uv.x * .1);
	uv.y = uv.y * .1 - floor(uv.y * .1);
	if (p->texture->img)
		r->color = get_color_img(p->texture, p->texture->buf, uv);
	if (p->texture->buf_n)
		set_normal_from_map(r, p->texture, uv);
	pthread_mutex_unlock(&p->texture->text_mutex);
}
