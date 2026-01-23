/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 11:55:49 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/19 14:27:54 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>

/**
 * @brief get_color_img
 *
 * Pour des coordonne dans une texture retourne la couleur
 *
 * @param t_texture *texture 
 * @param char *buf 
 * @param t_vec3 uv 
 * @return t_vec3 color
 */
t_vec3	get_color_img(t_texture *t, char *buf, t_vec3 uv)
{
	t_vec3	color;
	int		x;
	int		y;

	x = uv.x * t->w;
	y = uv.y * t->h;
	if (!buf)
		return ((t_vec3){0, 0, 0});
	color.z = (unsigned char)buf[(y * t->lb) + ((t->w - x) * 4)];
	color.y = (unsigned char)buf[(y * t->lb) + ((t->w - x) * 4) + 1];
	color.x = (unsigned char)buf[(y * t->lb) + ((t->w - x) * 4) + 2];
	return (color);
}

/**
 * @brief set_normal_from_map
 *
 * Definit la nouvelle normal dun point a partir d'ube bornalmap
 *
 * @param t_ray_d *r 
 * @param t_texture *texture 
 * @param t_vec3 uv 
 */
void	set_normal_from_map(t_ray_d *r, t_texture *texture, t_vec3 uv)
{
	t_vec3	per;
	t_vec3	tang;
	t_vec3	bi;
	t_vec3	final;
	t_vec3	col;

	col = get_color_img(texture, texture->buf_n, uv);
	col.x = col.x / 127 - 1;
	col.y = col.y / 127 - 1;
	col.z = col.z / 127 - 1;
	per = (t_vec3){1., 0., 0.};
	if (fabs(r->n.x) >= .5)
		per = (t_vec3){0, 1., 0};
	tang = normalize(vec_cross(per, r->n));
	bi = normalize(vec_cross(tang, r->n));
	final.x = tang.x * col.x + bi.x * col.y + r->n.x * col.z;
	final.y = tang.y * col.x + bi.y * col.y + r->n.y * col.z;
	final.z = tang.z * col.x + bi.z * col.y + r->n.z * col.z;
	r->n = normalize(final);
}
