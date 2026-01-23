/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:11:08 by jodde             #+#    #+#             */
/*   Updated: 2026/01/18 16:07:50 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

t_vec3	vec_mul(t_vec3 a, float t)
{
	t_vec3	vec;

	vec.x = a.x * t;
	vec.y = a.y * t;
	vec.z = a.z * t;
	return (vec);
}

t_vec3	vec_mul_vec(t_vec3 a, t_vec3 b)
{
	t_vec3	r;

	r.x = a.x * b.x;
	r.y = a.y * b.y;
	r.z = a.z * b.z;
	return (r);
}

float	vec_dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3	vec_cross(t_vec3 a, t_vec3 b)
{
	t_vec3	vec;

	vec.x = a.y * b.z - a.z * b.y;
	vec.y = a.z * b.x - a.x * b.z;
	vec.z = a.x * b.y - a.y * b.x;
	return (vec);
}

t_vec3	vec_fmin(float max, t_vec3 a)
{
	a.x = fmin(max, a.x);
	a.y = fmin(max, a.y);
	a.z = fmin(max, a.z);
	return (a);
}
