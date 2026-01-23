/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 15:49:49 by jodde             #+#    #+#             */
/*   Updated: 2026/01/16 15:50:54 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <limits.h>
#include <math.h>

float	plane_t_world(t_plane *plane, t_ray ray, float t)
{
	t_vec3	p_local;
	t_vec3	p_world;
	float	t_world;

	p_local = vec_add(ray.origin_loc, vec_mul(ray.dir_loc, t));
	p_world = vec_add(quat_rotate_vec(plane->q, p_local), plane->pos);
	t_world = vec_length(vec_sub(p_world, ray.origin));
	return (t_world);
}
