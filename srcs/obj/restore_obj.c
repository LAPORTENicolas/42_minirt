/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:30:15 by jodde             #+#    #+#             */
/*   Updated: 2026/01/19 20:29:08 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>
#include <limits.h>
#include <float.h>

void	restore_obj(t_env *env, void *obj)
{
	t_obj_type	type;

	if (!obj || env->selected_obj == NO_OBJ)
		return ;
	type = *((t_obj_type *)obj);
	if (type == SPHERE && env->selected_obj == SPHERE_OBJ)
		restore_sphere(env, (t_sphere *)obj);
	else if (type == PLANE && env->selected_obj == PLANE_OBJ)
		restore_plane(env, (t_plane *)obj);
	else if (type == CYLINDER && env->selected_obj == CYLINDER_OBJ)
		restore_cylinder(env, (t_cylinder *)obj);
}

void	restore_sphere(t_env *env, t_sphere *sphere)
{
	t_sphere	*backup;

	backup = env->backup_sphere;
	sphere->type = backup->type;
	sphere->r = backup->r;
	sphere->pos = backup->pos;
	sphere->color = backup->color;
	sphere->texture = backup->texture;
}

void	restore_plane(t_env *env, t_plane *plane)
{
	t_plane	*backup;

	backup = env->backup_plane;
	plane->type = backup->type;
	plane->pos = backup->pos;
	plane->n = backup->n;
	plane->color = backup->color;
}

void	restore_cylinder(t_env *env, t_cylinder *cylinder)
{
	t_cylinder	*backup;

	backup = env->backup_cylinder;
	cylinder->type = backup->type;
	cylinder->pos = backup->pos;
	cylinder->axis = backup->axis;
	cylinder->r = backup->r;
	cylinder->height = backup->height;
	cylinder->color = backup->color;
}
