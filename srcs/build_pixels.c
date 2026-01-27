/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pixels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:28:12 by jodde             #+#    #+#             */
/*   Updated: 2026/01/27 07:33:49 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <limits.h>
#include <pthread.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
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


t_vec3	color_beer(t_vec3 color, double t, t_vec3 glass_color)
{
	t_vec3	r;
	t_vec3	color_coef;

	(void)color;
	color_coef.x = (glass_color.x * 0.003921568627) * .4;
	color_coef.y = (glass_color.y * 0.003921568627) * .4;
	color_coef.z = (glass_color.z * 0.003921568627) * .4;
	r.x = color.x * exp(-color_coef.x * t);
	r.y = color.y * exp(-color_coef.y * t);
	r.z = color.z * exp(-color_coef.z * t);
	return (r);
}

/**
 *
 * Gere le rendu des rayons qui touche du verre
 *
 * @param t_env *env 1
 * @param t_ray_d *l_ray 
 * @param t_ray *ray 
 */
t_ray_d	render_glass_one_ray(t_env *env, t_ray_d l_ray, float n1, float n2)
{
	t_sphere	*sphere;
	t_ray		r_tmp;
	float		t;
	float		t2;

	sphere = l_ray.obj;
	r_tmp.origin = l_ray.hp;
	r_tmp.dir = normalize(refract(normalize(l_ray.ray.dir), normalize(l_ray.n), n1));
	t = fmax(0.1, check_sphere_hit(r_tmp, sphere, &t2));
	if (t < t2)
		t = t2;
	r_tmp.origin = vec_add(r_tmp.origin, vec_mul(r_tmp.dir, t));
	l_ray.n = normalize(vec_sub(r_tmp.origin, sphere->pos));
	r_tmp.dir = normalize(refract(r_tmp.dir,l_ray.n, n2));
	l_ray = get_pixel_color(env, r_tmp, sphere);
	return (l_ray);
}

void	render_glass(t_env *env, t_ray_d *l_ray)
{
	t_vec3	final_color;
	t_ray_d	ray_data;

	ray_data = render_glass_one_ray(env, *l_ray, 0.58, 1.58);
	ray_data.color = color_beer(ray_data.color, ray_data.t, ((t_sphere *)l_ray->obj)->pos);
	final_color.x = ray_data.color.x;
	ray_data = render_glass_one_ray(env, *l_ray, 0.62, 1.62);
	ray_data.color = color_beer(ray_data.color, ray_data.t, ((t_sphere *)l_ray->obj)->pos);
	final_color.z = ray_data.color.z;
	ray_data = render_glass_one_ray(env, *l_ray, 0.60, 1.60);
	ray_data.color = color_beer(ray_data.color, ray_data.t, ((t_sphere *)l_ray->obj)->pos);
	final_color.y = ray_data.color.y;
	*l_ray = ray_data;
	l_ray->color = final_color;
	l_ray->glass_flag = 0;
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
