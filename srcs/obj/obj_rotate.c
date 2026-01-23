/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:13:56 by jodde             #+#    #+#             */
/*   Updated: 2026/01/19 13:25:19 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>
#include <limits.h>
#include <float.h>

t_vec3	quat_rotate_vec(t_quat q, t_vec3 v)
{
	t_quat	vq;
	t_quat	rq;
	t_quat	qi;

	vq = (t_quat){0, v.x, v.y, v.z};
	qi = q_conj(q);
	rq = q_mul(q_mul(q, vq), qi);
	return ((t_vec3){rq.x, rq.y, rq.z});
}

int	handle_key(int key, t_quat *delta)
{
	if (key == Q_KEY)
		*delta = quat_axis_angle((t_vec3){1, 0, 0}, ROT_ANGLE);
	else if (key == E_KEY)
		*delta = quat_axis_angle((t_vec3){1, 0, 0}, -ROT_ANGLE);
	else if (key == A_KEY)
		*delta = quat_axis_angle((t_vec3){0, 1, 0}, ROT_ANGLE);
	else if (key == D_KEY)
		*delta = quat_axis_angle((t_vec3){0, 1, 0}, -ROT_ANGLE);
	else if (key == Z_KEY)
		*delta = quat_axis_angle((t_vec3){0, 0, 1}, ROT_ANGLE);
	else if (key == C_KEY)
		*delta = quat_axis_angle((t_vec3){0, 0, 1}, -ROT_ANGLE);
	else
		return (0);
	return (1);
}

void	rotate_obj(int key, t_env *env)
{
	t_plane		*plane;
	t_cylinder	*cyl;
	t_cone		*co;
	t_quat		delta;

	if (!env->obj || env->selected_obj == SPHERE_OBJ)
		return ;
	if (!handle_key(key, &delta))
		return ;
	if (env->selected_obj == PLANE_OBJ)
	{
		plane = (t_plane *)env->obj;
		plane->q = normalize_q(q_mul(delta, plane->q));
	}
	else if (env->selected_obj == CYLINDER_OBJ)
	{
		cyl = (t_cylinder *)env->obj;
		cyl->q = normalize_q(q_mul(delta, cyl->q));
	}
	else if (env->selected_obj == CONE_OBJ)
	{
		co = (t_cone *)env->obj;
		co->q = normalize_q(q_mul(delta, co->q));
	}
	env->win.need_reset = 1;
}
