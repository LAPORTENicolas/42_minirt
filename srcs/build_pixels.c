/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pixels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:28:12 by jodde             #+#    #+#             */
/*   Updated: 2026/01/28 06:47:19 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <limits.h>
#include <pthread.h>
#include <float.h>
#include <string.h>

/**
 * @brief check_all_objects
 *
 * Verifie toutes les intersections puis
 * retourne le plus proche
 *
 * @param t_scene scene
 * @param t_ray ray
 *
 * @return t_ray_d most_short
 */
t_ray_d	check_all_objects(t_env *env, \
		t_ray ray, void *last, int light)
{
	t_ray_d	r[4];
	t_scene	scene;

	ft_memset(r, 0, sizeof(t_ray_d) * 4);
	scene = env->scene;
	r[0].t = FLT_MAX;
	r[1].t = FLT_MAX;
	r[2].t = FLT_MAX;
	r[3].t = FLT_MAX;
	r[0] = check_all_planes(ray, scene.planes, last, light);
	r[1] = check_all_spheres(env, ray, last, light);
	r[2] = check_all_cylinders(env, ray, last, light);
	r[3] = check_all_cones(env, ray, last, light);
	if (r[1].t < r[0].t)
		r[0] = r[1];
	if (r[2].t < r[0].t)
		r[0] = r[2];
	if (r[3].t < r[0].t)
		r[0] = r[3];
	return (r[0]);
}

t_vec3	shoot_ray(t_env *env, t_ray_d *l_ray, t_ray *ray)
{
	int		i;
	t_vec3	return_color;

	i = 0;
	return_color = (t_vec3){0., 0., 0.};
	while (i < 2)
	{
		*l_ray = get_pixel_color(env, *ray, NULL);
		if (l_ray->t == FLT_MAX)
			return (return_color);
		if (i == 0)
			ray->reflection = l_ray->reflection;
		if (ray->mirror && i == 1)
			ray->mul = .7;
		if (i == 0 && l_ray->reflection == 1.)
			ray->mirror = 1;
		if (l_ray->glass_flag)
			render_glass(env, l_ray);
		return_color = vec_add(return_color, vec_mul(l_ray->color, ray->mul));
		ray->mul *= ray->reflection;
		ray->origin = l_ray->hp;
		ray->dir = reflect(l_ray->ray.dir, l_ray->n, l_ray->roughness);
		i++;
	}
	return (return_color);
}

/**
 * @brief render_one_pixel
 *
 * Pour un pixel, retourne la couleur de ce pixel
 *
 * @param t_env *env 
 * @param t_scene scene 
 * @param t_ray ray 
 * @return t_vec3 color
 */
t_vec3	render_one_pixel(t_env *env, t_ray ray)
{
	t_ray_d	l_ray;

	ft_memset(&l_ray, 0, sizeof(t_ray_d));
	ray.mul = .6;
	ray.mirror = 0;
	return (shoot_ray(env, &l_ray, &ray));
}
