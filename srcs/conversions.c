/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:09:34 by jodde             #+#    #+#             */
/*   Updated: 2026/01/15 16:18:20 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../lib/mlx/mlx.h"
#include <limits.h>
#include <math.h>
#include <float.h>

void	coordinate_from_mouse(t_env *env, float *x, float *y)
{
	*x = (2 * ((env->mouse_x) + 0.5) / (float)env->win.width - 1);
	*y = (1 - 2 * ((env->mouse_y) + 0.5) / (float)env->win.height);
}

void	coordinate_from_index(t_env *env, int index, float *x, float *y)
{
	*x = (2 * ((index % env->win.width) + 0.5) / (float)env->win.width - 1);
	*y = (1 - 2 * ((index / env->win.width) + 0.5) / (float)env->win.height);
}

float	calc_rad(float degree)
{
	return (degree * M_PI / 180.0f);
}
