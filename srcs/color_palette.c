/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_palette.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:48:28 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/20 10:03:42 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#define TWOP 6.28318530718

t_vec3	palette1(float t)
{
	t_vec3	pale;
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	t_vec3	d;

	a = (t_vec3){0.5, 0.5, 0.5};
	b = (t_vec3){0.5, 0.5, 0.5};
	c = (t_vec3){1, 1, 1};
	d = (t_vec3){0.30, 0.20, 0.20};
	pale.x = a.x + b.x * cos(TWOP * (c.x * t + d.x));
	pale.y = a.y + b.y * cos(TWOP * (c.y * t + d.y));
	pale.z = a.z + b.z * cos(TWOP * (c.z * t + d.z));
	return (pale);
}

t_vec3	palette2(float t)
{
	t_vec3	pale;
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	t_vec3	d;

	a = (t_vec3){0.51, 0.51, 0.51};
	b = (t_vec3){0.495, 0.495, 0.495};
	c = (t_vec3){0.81, 0.81, 0.81};
	d = (t_vec3){-.692, -.592, -.492};
	pale.x = a.x + b.x * cos(TWOP * (c.x * t + d.x));
	pale.y = a.y + b.y * cos(TWOP * (c.y * t + d.y));
	pale.z = a.z + b.z * cos(TWOP * (c.z * t + d.z));
	return (pale);
}

t_vec3	palette3(float t)
{
	t_vec3	pale;
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	t_vec3	d;

	a = (t_vec3){0.5, 0.5, 0.5};
	b = (t_vec3){0.5, 0.5, 0.5};
	c = (t_vec3){2.0, 1.0, 0.0};
	d = (t_vec3){0.50, 0.20, 0.25};
	pale.x = a.x + b.x * cos(TWOP * (c.x * t + d.x));
	pale.y = a.y + b.y * cos(TWOP * (c.y * t + d.y));
	pale.z = a.z + b.z * cos(TWOP * (c.z * t + d.z));
	return (pale);
}

t_vec3	palette4(float t)
{
	t_vec3	pale;
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	t_vec3	d;

	a = (t_vec3){.518, -0.252, 0.470};
	b = (t_vec3){0.770, 1.230, 0.560};
	c = (t_vec3){1.008, 0.500, 1.030};
	d = (t_vec3){0.498, 0.783, 0.727};
	pale.x = a.x + b.x * cos(TWOP * (c.x * t + d.x));
	pale.y = a.y + b.y * cos(TWOP * (c.y * t + d.y));
	pale.z = a.z + b.z * cos(TWOP * (c.z * t + d.z));
	return (pale);
}

t_vec3	palette5(float t)
{
	t_vec3	pale;
	t_vec3	a;
	t_vec3	b;
	t_vec3	c;
	t_vec3	d;

	a = (t_vec3){.500, 0.088, -2.472};
	b = (t_vec3){0.5, 0.5, 0.5};
	c = (t_vec3){0.333, 0.500, 0.333};
	d = (t_vec3){0.667, 0.500, 0.667};
	pale.x = a.x + b.x * cos(TWOP * (c.x * t + d.x));
	pale.y = a.y + b.y * cos(TWOP * (c.y * t + d.y));
	pale.z = a.z + b.z * cos(TWOP * (c.z * t + d.z));
	return (pale);
}
