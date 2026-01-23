/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:10:54 by jodde             #+#    #+#             */
/*   Updated: 2026/01/18 14:13:08 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

float	vec_length(t_vec3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

float	vec_length2(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3	normalize(t_vec3 v)
{
	float	len;
	t_vec3	vec;

	len = vec_length(v);
	if (len < EPS)
	{
		vec.x = 0;
		vec.y = 0;
		vec.z = 0;
	}
	else
	{
		vec.x = v.x / len;
		vec.y = v.y / len;
		vec.z = v.z / len;
	}
	return (vec);
}

t_vec3	vec_add(t_vec3 a, t_vec3 b)
{
	t_vec3	vec;

	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	return (vec);
}

t_vec3	vec_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	vec;

	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	vec.z = a.z - b.z;
	return (vec);
}
