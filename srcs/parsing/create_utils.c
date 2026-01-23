/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 20:30:28 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/21 16:57:02 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <float.h>
#include <unistd.h>
#include <math.h>

void	init_cylinder(t_cylinder *cy, char **split)
{
	cy->r = ft_atof(split[3]) / 2.0f;
	cy->height = ft_atof(split[4]);
	cy->top = vec_add(cy->pos, vec_mul(cy->axis, cy->height));
	cy->bottom = cy->pos;
	cy->type = CYLINDER;
	cy->q = quat_from_to((t_vec3){0, 1, 0}, cy->axis);
}

void	init_cone(t_cone *cone, char **split)
{
	cone->r = ft_atof(split[3]) / 2.0f;
	cone->height = ft_atof(split[4]);
	cone->axis = normalize(cone->axis);
	cone->phi = atan(cone->r / cone->height);
	cone->q = quat_from_to((t_vec3){0, 1, 0}, cone->axis);
	cone->k = (cone->r / cone->height) * (cone->r / cone->height);
	cone->type = CONE;
}
