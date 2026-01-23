/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:13:56 by jodde             #+#    #+#             */
/*   Updated: 2026/01/21 15:11:15 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>
#include <limits.h>
#include <float.h>

int	identify_obj_type(t_ray_d ray_d, t_env *env)
{
	if (!ray_d.obj)
	{
		env->selected_obj = NO_OBJ;
		return (0);
	}
	if (ray_d.type == SPHERE)
		env->selected_obj = SPHERE_OBJ;
	else if (ray_d.type == PLANE)
		env->selected_obj = PLANE_OBJ;
	else if (ray_d.type == CYLINDER)
		env->selected_obj = CYLINDER_OBJ;
	else if (ray_d.type == CONE)
		env->selected_obj = CONE_OBJ;
	env->obj = ray_d.obj;
	return (1);
}

void	select_object(t_env *env)
{
	t_ray_d		ray_d;
	float		x;
	float		y;

	x = 0;
	y = 0;
	coordinate_from_mouse(env, &x, &y);
	ray_d = check_all_objects(env, gen_world_ray(env, x, y), NULL, 0);
	if (ray_d.t != FLT_MAX)
	{
		if (!identify_obj_type(ray_d, env))
			return ;
		else
			snapshot_obj(env, ray_d.obj);
	}
}
