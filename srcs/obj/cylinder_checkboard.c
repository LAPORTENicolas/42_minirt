/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_checkboard.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:30:25 by jodde             #+#    #+#             */
/*   Updated: 2026/01/21 21:20:27 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>
#include <stdio.h>

void	cyl_checkboard_disk(t_ray_d *r, float radius)
{
	float	ra;
	float	a;	
	int		ring;
	int		sector;

	a = atan2(r->hp_loc.z, r->hp_loc.x);
	ra = sqrt(r->hp_loc.x * r->hp_loc.x + r->hp_loc.z * r->hp_loc.z);
	ring = (int)((ra / radius) * 6);
	sector = (int)((a + M_PI) / (2 * M_PI) * 12);
	if ((ring + sector) & 1)
		r->color = (t_vec3){255, 255, 255};
	else
		r->color = (t_vec3){0, 0, 0};
}

void	cyl_checkboard_side(t_vec3 uv, t_ray_d *r)
{
	int	iu;
	int	iv;

	iv = (int)(uv.x * 32);
	iu = (int)(uv.y * 16);
	if ((iu + iv) & 1)
		r->color = (t_vec3){255, 255, 255};
	else
		r->color = (t_vec3){0, 0, 0};
}
