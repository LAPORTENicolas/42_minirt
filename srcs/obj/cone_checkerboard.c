/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_checkerboard.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:30:25 by jodde             #+#    #+#             */
/*   Updated: 2026/01/21 21:19:12 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <math.h>

void	cone_checkboard_disk(t_ray_d *r, float radius)
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

void	cone_checkboard_side(t_vec3 uv, t_ray_d *r, t_cone *cone)
{
	int	ring;
	int	sector;

	(void) cone;
	if (r->hp_loc.y <= 0)
		return ;
	ring = (int)(uv.y * 16);
	sector = (int)(atan2(r->hp_loc.z, r->hp_loc.x) * 8);
	if ((ring + sector) & 1)
		r->color = (t_vec3){255, 255, 255};
	else
		r->color = (t_vec3){0, 0, 0};
}
