/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:13:56 by jodde             #+#    #+#             */
/*   Updated: 2026/01/21 14:36:31 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>
#include <limits.h>
#include <float.h>

void	resize_sphere(t_env *env, int direction)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)env->obj;
	if (direction > 0)
		sphere->r += 0.2f;
	else if (direction < 0 && sphere->r > 0.2f)
		sphere->r -= 0.2f;
}

void	resize_cylinder(t_env *env, int direction)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder *)env->obj;
	if (direction > 0)
		cyl->r += 0.2f;
	else if (direction < 0 && cyl->r > 0.2f)
		cyl->r -= 0.2f;
}

void	resize_cone(t_env *env, int direction)
{
	t_cone	*cone;

	cone = (t_cone *)env->obj;
	if (direction > 0)
	{
		cone->r += 0.2f;
		cone->height = cone->r / tan(cone->phi);
	}
	else if (direction < 0 && cone->r > 0.2f)
	{
		cone->r -= 0.2f;
		cone->height = cone->r / tan(cone->phi);
	}
}

void	resize_object(t_env *env, int direction)
{
	if (env->selected_obj == NO_OBJ)
		return ;
	if (env->selected_obj == SPHERE_OBJ)
		resize_sphere (env, direction);
	else if (env->selected_obj == PLANE_OBJ)
		return ;
	else if (env->selected_obj == CYLINDER_OBJ)
		resize_cylinder(env, direction);
	else if (env->selected_obj == CONE_OBJ)
		resize_cone(env, direction);
}
