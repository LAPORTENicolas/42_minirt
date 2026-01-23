/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quat_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:10:54 by jodde             #+#    #+#             */
/*   Updated: 2026/01/21 16:07:57 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math.h"

t_quat	q_conj(t_quat q)
{
	t_quat	p;

	p.w = q.w;
	p.x = -q.x;
	p.y = -q.y;
	p.z = -q.z;
	return (p);
}

t_quat	q_mul(t_quat p, t_quat q)
{
	t_quat	result;

	result.w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
	result.x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
	result.y = p.w * q.y - p.x * q.z + p.y * q.w + p.z * q.x;
	result.z = p.w * q.z + p.x * q.y - p.y * q.x + p.z * q.w;
	return (result);
}

t_quat	normalize_q(t_quat q)
{
	float	norm;
	t_quat	result;

	norm = sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	if (norm < EPS)
	{
		result.w = 0;
		result.x = 0;
		result.y = 0;
		result.z = 0;
		return (result);
	}
	result.w = q.w / norm;
	result.x = q.x / norm;
	result.y = q.y / norm;
	result.z = q.z / norm;
	return (result);
}

t_quat	quat_axis_angle(t_vec3 axis, float angle)
{
	t_quat	q;
	float	s;

	axis = normalize(axis);
	s = sin(angle / 2.0f);
	q.w = cos(angle / 2.0f);
	q.x = axis.x * s;
	q.y = axis.y * s;
	q.z = axis.z * s;
	return (q);
}

t_vec3	change_axis(t_vec3 axis)
{
	t_vec3	result;

	if (fabs(axis.x) < fabs(axis.z))
		result = (t_vec3){0.0f, 0.0f, 1.0f};
	else
		result = (t_vec3){1.0f, 0.0f, 0.0f};
	return (result);
}
