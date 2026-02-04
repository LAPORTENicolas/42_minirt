/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_texture_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:30:25 by jodde             #+#    #+#             */
/*   Updated: 2026/02/04 23:28:26 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>

void	apply_cone_texture_wrap(t_vec3 *uv, t_ray_d *r, t_cone *co)
{
	uv->x = fmod(uv->x, 1);
	uv->y = fmod(uv->y, 1);
	if (isnan(uv->x) || isnan(uv->y))
		return (ft_memset (uv, 0, sizeof(t_vec3)), (void) NULL);
	if (!co->hit_type)
	{
		r->color = get_color_img(co->texture, co->texture->buf, *uv);
		if (co->texture->buf_n)
			set_normal_from_map(r, co->texture, *uv);
	}
	if (co->hit_type)
	{
		uv->x = (r->hp_loc.x / co->r + 1.0f) / 2.0f;
		uv->y = (r->hp_loc.z / co->r + 1.0f) / 2.0f;
		r->color = get_color_img(co->texture, co->texture->buf, *uv);
		if (co->texture->buf_n)
			set_normal_from_map(r, co->texture, *uv);
	}
}

void	manage_cone_texture(t_ray_d *r, t_cone *cone)
{
	t_vec3	uv;
	float	theta;

	theta = atan2(r->hp_loc.z, r->hp_loc.x);
	uv.x = (theta + M_PI) / (2.0f * M_PI);
	uv.y = r->hp_loc.y / cone->height;
	if (cone->checkboard_flag)
	{
		if (!cone->hit_type)
			return (cone_checkboard_side(uv, r, cone));
		return (cone_checkboard_disk(r, cone->r));
	}
	if (cone->pal_flag)
		cone->color = vec_mul(cone->pal(uv.x * uv.y * 4), 255);
	if (!cone->texture)
		return ;
	pthread_mutex_lock(&cone->texture->text_mutex);
	r->reflection = cone->texture->reflection;
	r->roughness = cone->texture->rougness;
	if (cone->texture->buf)
		apply_cone_texture_wrap(&uv, r, cone);
	if (cone->texture->buf)
		apply_cone_texture_wrap(&uv, r, cone);
	pthread_mutex_unlock(&cone->texture->text_mutex);
}
