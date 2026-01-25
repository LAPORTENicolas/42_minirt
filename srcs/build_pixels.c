/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pixels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:28:12 by jodde             #+#    #+#             */
/*   Updated: 2026/01/25 02:30:26 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <limits.h>
#include <pthread.h>
#include <float.h>
#include <math.h>
#include <stdio.h>

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

/**
 * @brief get_ray_from_glass
 *
 *	Calcul les rayon refracter et reflect pour chaque canal R,V,B
 *
 * @param t_env *env 
 * @param t_ray *ray 
 * @param t_ray *l_ray 
 * @param t_ray *ray_return 
 */
t_vec3	get_ray_from_glass(t_env *env, t_ray *ray, \
		t_ray_d *l_ray, t_ray_d *ray_return)
{
	float	dispertion;
	t_vec3	exit_dir;
	t_vec3	color;

	dispertion = 0.;
	exit_dir = refract(ray->dir, l_ray->n, 0.6);
	ft_memset(&color, 0, sizeof(t_vec3));
	ray->dir = vec_add(exit_dir, get_random_vec(dispertion));
	ray_return[0] = get_pixel_color(env, *ray, l_ray->obj);
	if (ray_return[0].t <= 0 || ray_return[0].t >= 21473840)
		return (ft_memset(&ray_return[0].color, 0, \
					sizeof(t_vec3)), color);
	ray->dir = exit_dir;
	ray_return[2] = get_pixel_color(env, *ray, l_ray->obj);
	ray->dir = vec_add(exit_dir, get_random_vec(dispertion));
	ray_return[4] = get_pixel_color(env, *ray, l_ray->obj);
	color.x = ray_return[0].color.x * .7;
	color.y = ray_return[2].color.y * .7;
	color.z = ray_return[4].color.z * .7;
	return (color);
}

/**
 * @brief render_glass
 *
 * Gere le rendu des rayons qui touche du verre
 *
 * @param t_env *env 1
 * @param t_ray_d *l_ray 
 * @param t_ray *ray 
 */
void	render_glass(t_env *env, t_ray_d *l_ray, t_ray *ray)
{
	t_vec3	enter_dir;
	t_ray_d	ex[6];

	ft_memset(&ex, 0, sizeof(t_ray_d) * 6);
	enter_dir = refract(ray->dir, l_ray->n, 1.6);
	if (vec_dot(enter_dir, enter_dir) == .0)
	{
		ray->origin = l_ray->hp;
		ray->dir = reflect(ray->dir, l_ray->n, 0.);
		*l_ray = get_pixel_color(env, *ray, l_ray->obj);
	}
	else
	{
		if (l_ray->type == PLANE && vec_dot(ray->dir, l_ray->n) > 0)
			l_ray->n = vec_mul(l_ray->n, -1);
		ray->origin = l_ray->hp;
		ex[0].color = get_ray_from_glass(env, ray, l_ray, ex);
		if (fabs(ex[0].color.x + ex[0].color.y + ex[0].color.z) <= 1.)
			return (l_ray->glass_flag = 0, \
	ft_memset(&l_ray->color, 0, sizeof(t_vec3)), (void)(NULL));
		*l_ray = ex[0];
		ray->mul = 1.;
	}
}

/**
 * @brief shoot_ray
 *
 * Tire un rayon avec un nombre defini de rebond
 * puis retourne la couleur final du rayon/pixel
 *
 * @param t_env *env 
 * @param t_ray *l_ray 
 * @param t_ray *ray 
 * @return 
 */
t_vec3	shoot_ray(t_env *env, t_ray_d *l_ray, t_ray *ray)
{
	int		i;
	t_vec3	return_color;

	i = 0;
	return_color = (t_vec3){0., 0., 0.};
	while (i < 3)
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
		while (l_ray->glass_flag)
			render_glass(env, l_ray, ray);
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
