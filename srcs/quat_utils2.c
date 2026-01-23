/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:10:54 by jodde             #+#    #+#             */
/*   Updated: 2026/01/21 16:08:11 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math.h"

t_quat	identity_q(void)
{
	t_quat	q;

	q.w = 1.0f;
	q.x = 0.0f;
	q.y = 0.0f;
	q.z = 0.0f;
	return (q);
}

t_quat	quat_from_to(t_vec3 from, t_vec3 to)
{
	t_quat	q;
	t_vec3	axis;
	float	dot;

	from = normalize(from);
	to = normalize(to);
	dot = vec_dot(from, to);
	if (dot > 1.0f - EPS)
		return (identity_q());
	if (dot < -1.0f + EPS)
	{
		axis = vec_cross((t_vec3){1, 0, 0}, from);
		if (vec_length(axis) < EPS)
			axis = vec_cross((t_vec3){0, 0, 1}, from);
		axis = normalize(axis);
		q = (t_quat){0, axis.x, axis.y, axis.z};
		return (q);
	}
	axis = vec_cross(from, to);
	q = (t_quat){1.0f + dot, axis.x, axis.y, axis.z};
	return (normalize_q(q));
}
