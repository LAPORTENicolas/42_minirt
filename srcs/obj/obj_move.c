/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 10:50:04 by jodde             #+#    #+#             */
/*   Updated: 2026/01/21 15:09:34 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>
#include <limits.h>
#include <float.h>

void	move_obj(int key, t_env *env, t_vec3 *objpos)
{
	if (key == W_KEY)
		objpos->y += 0.2f;
	if (key == S_KEY)
		objpos->y -= 0.2f;
	if (key == D_KEY)
		objpos->x += 0.2f;
	if (key == A_KEY)
		objpos->x -= 0.2f;
	if (key == UP_KEY)
		objpos->z += 0.2f;
	if (key == DOWN_KEY)
		objpos->z -= 0.2f;
	env->win.need_reset = 1;
}

void	keyboard_move_object2(int key, t_env *env)
{
	t_cone		*cone;
	t_light		*light;

	if (env->selected_obj == CONE_OBJ)
	{
		cone = (t_cone *)env->obj;
		move_obj(key, env, &cone->pos);
	}
	else if (env->selected_obj == LIGHT_OBJ)
	{
		light = env->light_to_move2;
		move_obj(key, env, &light->pos);
	}
	return ;
}

void	keyboard_move_object(int key, t_env *env)
{
	t_sphere	*sphere;
	t_cylinder	*cyl;
	t_plane		*plane;

	if (env->mouse_left)
		rotate_obj(key, env);
	else if (env->selected_obj == SPHERE_OBJ)
	{
		sphere = (t_sphere *)env->obj;
		move_obj(key, env, &sphere->pos);
	}
	else if (env->selected_obj == CYLINDER_OBJ)
	{	
		cyl = (t_cylinder *)env->obj;
		move_obj(key, env, &cyl->pos);
	}	
	else if (env->selected_obj == PLANE_OBJ)
	{
		plane = (t_plane *)env->obj;
		move_obj(key, env, &plane->pos);
	}
	keyboard_move_object2(key, env);
}
