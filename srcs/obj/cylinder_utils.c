/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:30:25 by jodde             #+#    #+#             */
/*   Updated: 2026/01/21 20:35:07 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>

void	set_cyl_data(t_ray_d *r, t_cylinder *cyl, float t)
{
	cylinder_hp_n(cyl, r, t);
	r->color = cyl->color;
	r->obj = cyl;
	r->type = CYLINDER;
	r->roughness = 0.0f;
	r->reflection = 0.1f;
	r->glass_flag = cyl->glass_flag;
	if (cyl->texture || cyl->checkboard_flag || cyl->pal_flag)
		manage_cyl_texture(r, cyl);
}

float	cylinder_height(t_ray ray, t_cylinder *cyl, float t)
{
	t_vec3	p;
	float	h;

	p = vec_add(ray.origin_loc, vec_mul(ray.dir_loc, t));
	h = p.y;
	if (h < 0.0f || h > cyl->height)
		return (-1);
	return (t);
}

t_vec3	cylinder_normal_local(t_vec3 p_local, int hit_type)
{
	if (hit_type == 0)
		return (normalize((t_vec3){p_local.x, 0.0f, p_local.z}));
	if (hit_type == 1)
		return ((t_vec3){0.0f, -1.0f, 0.0f});
	return ((t_vec3){0.0f, 1.0f, 0.0f});
}

void	cylinder_hp_n(t_cylinder *cy, t_ray_d *r, float t)
{
	t_vec3	n_local;

	r->hp_loc = vec_add(r->ray.origin_loc, vec_mul(r->ray.dir_loc, t));
	n_local = cylinder_normal_local(r->hp_loc, cy->hit_type);
	r->hp = vec_add(quat_rotate_vec(cy->q, r->hp_loc), cy->pos);
	r->n = normalize(quat_rotate_vec(cy->q, n_local));
	if (vec_dot(r->n, r->ray.dir) > 0.0f)
		r->n = vec_mul(r->n, -1.0f);
}

float	cyl_t_world(t_cylinder *cyl, t_ray ray, t_vec3 *hp_loc, float t)
{
	t_vec3	p_world;
	float	t_world;

	*hp_loc = vec_add(ray.origin_loc, vec_mul(ray.dir_loc, t));
	p_world = vec_add(quat_rotate_vec(cyl->q, *hp_loc), cyl->pos);
	t_world = vec_length(vec_sub(p_world, ray.origin));
	return (t_world);
}
