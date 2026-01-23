/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snapshot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 12:13:10 by jodde             #+#    #+#             */
/*   Updated: 2026/01/19 20:30:40 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>
#include <limits.h>
#include <float.h>
#include <stdio.h>

void	copy_sphere(t_env *env, t_sphere *sphere)
{
	t_sphere	*backup;

	backup = malloc(sizeof(t_sphere));
	if (!backup)
	{
		perror("Error: malloc copy_sphere");
		return ;
	}
	env->backup_sphere = backup;
	backup->type = sphere->type;
	backup->r = sphere->r;
	backup->pos = sphere->pos;
	backup->q = sphere->q;
	backup->color = sphere->color;
	backup->texture = sphere->texture;
}

void	copy_plane(t_env *env, t_plane *plane)
{
	t_plane	*backup;

	backup = malloc(sizeof(t_plane));
	if (!backup)
	{
		perror("Error: malloc copy_plane");
		return ;
	}
	env->backup_plane = backup;
	backup->type = plane->type;
	backup->pos = plane->pos;
	backup->q = plane->q;
	backup->n = plane->n;
	backup->color = plane->color;
}	

void	copy_cylinder(t_env *env, t_cylinder *cylinder)
{
	t_cylinder	*backup;

	backup = malloc(sizeof(t_cylinder));
	if (!backup)
	{
		perror("Error: malloc copy_cylinder");
		return ;
	}
	env->backup_cylinder = backup;
	backup->type = cylinder->type;
	backup->pos = cylinder->pos;
	backup->axis = cylinder->axis;
	backup->r = cylinder->r;
	backup->q = cylinder->q;
	backup->height = cylinder->height;
	backup->color = cylinder->color;
}

void	copy_cone(t_env *env, t_cone *cone)
{
	t_cone	*backup;

	backup = malloc(sizeof(t_cone));
	if (!backup)
	{
		perror("Error: malloc copy_cylinder");
		return ;
	}
	env->backup_cone = backup;
	backup->type = cone->type;
	backup->pos = cone->pos;
	backup->axis = cone->axis;
	backup->r = cone->r;
	backup->q = cone->q;
	backup->height = cone->height;
	backup->color = cone->color;
}

void	snapshot_obj(t_env *env, void *obj)
{
	if (env->selected_obj == SPHERE_OBJ)
		copy_sphere(env, (t_sphere *)obj);
	else if (env->selected_obj == PLANE_OBJ)
		copy_plane(env, (t_plane *)obj);
	else if (env->selected_obj == CYLINDER_OBJ)
		copy_cylinder(env, (t_cylinder *)obj);
	else if (env->selected_obj == CONE_OBJ)
		copy_cone(env, (t_cone *)obj);
}
