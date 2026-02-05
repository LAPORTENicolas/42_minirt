/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_texture_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:30:25 by jodde             #+#    #+#             */
/*   Updated: 2026/02/05 11:18:18 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>
#include <stdio.h>

void	apply_cyl_texture_wrap(t_vec3 *uv, t_ray_d *r, t_cylinder *cy)
{
	uv->x = fmod(uv->x, 1);
	uv->y = fmod(uv->y, 1);
	if (isnan(uv->x) || isnan(uv->y))
		return (ft_memset (uv, 0, sizeof(t_vec3)), (void) NULL);
	if (!cy->hit_type)
	{
		r->color = get_color_img(cy->texture, cy->texture->buf, *uv);
		if (cy->texture->buf_n)
			set_normal_from_map(r, cy->texture, *uv);
	}
	if (cy->hit_type)
	{
		uv->x = (r->hp_loc.x / cy->r + 1.0f) / 2.0f;
		uv->y = (r->hp_loc.z / cy->r + 1.0f) / 2.0f;
		r->color = get_color_img(cy->texture, cy->texture->buf, *uv);
		if (cy->texture->buf_n)
			set_normal_from_map(r, cy->texture, *uv);
	}
}

void	manage_cyl_texture(t_ray_d *r, t_cylinder *cy)
{
	t_vec3	uv;
	float	theta;

	uv.z = 0;
	theta = atan2(r->hp_loc.z, r->hp_loc.x);
	uv.x = (theta + M_PI) / (2.0f * M_PI);
	uv.y = (r->hp_loc.y + cy->height / 2.0f) / cy->height;
	if (cy->checkboard_flag && (cy->hit_type != 0))
		return (cyl_checkboard_disk(r, cy->r));
	if (cy->checkboard_flag && (cy->hit_type == 0))
		return (cyl_checkboard_side(uv, r));
	if (cy->pal_flag)
		cy->color = vec_mul(cy->pal(uv.x * 32 + uv.y * 16), 255);
	if (!cy->texture)
	 	return ;
	pthread_mutex_lock(&cy->texture->text_mutex);
	r->reflection = cy->texture->reflection;
	r->roughness = cy->texture->rougness;
	if (cy->texture->buf)
		apply_cyl_texture_wrap(&uv, r, cy);
	if (cy->texture->buf_n)
		set_normal_from_map(r, cy->texture, uv);
	pthread_mutex_unlock(&cy->texture->text_mutex);
}
