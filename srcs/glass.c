/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glass.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlaporte <nlaporte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 06:31:50 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/28 06:49:48 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

/**
 * @brief color
 *
 * Beer-Lambert atenuation de la lumiere dans lu verre
 * @param color 
 * @param t 
 * @param glass_color 
 * @return  float color
 */
float	color_beer(float color, double t, float glass_color)
{
	float	col;

	col = (glass_color * 0.003921568627) * .2;
	return (color * exp(-col * t));
}

/**
 *
 * Gere le rendu des rayons qui touche du verre
 *
 * @param t_env *env 1
 * @param t_ray_d *l_ray 
 * @param t_ray *ray 
 */
t_ray_d	render_glass_ray(t_env *env, t_ray_d l_ray, \
		float n[2], float *old_t)
{
	t_sphere	*sphere;
	t_ray		r_tmp;
	float		t;
	float		t2;

	sphere = l_ray.obj;
	r_tmp.origin = l_ray.hp;
	r_tmp.dir = normalize(refract(normalize(l_ray.ray.dir), \
				normalize(l_ray.n), n[0]));
	t = fmax(0.1, check_sphere_hit(r_tmp, sphere, &t2));
	if (t < t2)
		t = t2;
	*old_t = t;
	r_tmp.origin = vec_add(r_tmp.origin, vec_mul(r_tmp.dir, t));
	l_ray.n = normalize(vec_sub(r_tmp.origin, sphere->pos));
	if (vec_dot(l_ray.n, r_tmp.dir) < 0)
		l_ray.n = vec_mul(l_ray.n, -1);
	l_ray.n = vec_mul(l_ray.n, -1);
	r_tmp.dir = normalize(refract(r_tmp.dir, l_ray.n, n[1]));
	l_ray.ray.dir = r_tmp.dir;
	l_ray.ray.origin = r_tmp.origin;
	l_ray = check_all_objects(env, l_ray.ray, sphere, 0);
	return (l_ray);
}

/**
 * @brief render_ior
 *
 * IOR Indice Of Refraction
 *
 * Refraction pour chaque cannal de couleur
 * Indice de refraction pour du verre 
 *
 * @param env 
 * @param l_ray 
 * @return t_ray_d
 */
t_ray_d	render_ior(t_env *env, t_ray_d *l_ray)
{
	t_ray_d	ray_data;
	t_vec3	final_color;
	float	t;

	ray_data = render_glass_ray(env, *l_ray, (float [2]){0.58, 1.58}, &t);
	ray_data.color.x = color_beer(ray_data.color.x, t, \
		((t_sphere *)l_ray->obj)->color.x);
	final_color.x = ray_data.color.x;
	ray_data = render_glass_ray(env, *l_ray, (float [2]){0.62, 1.62}, &t);
	ray_data.color.z = color_beer(ray_data.color.z, t, \
		((t_sphere *)l_ray->obj)->color.z);
	final_color.z = ray_data.color.z;
	ray_data = render_glass_ray(env, *l_ray, (float [2]){0.60, 1.60}, &t);
	ray_data.color.y = color_beer(ray_data.color.y, t, \
		((t_sphere *)l_ray->obj)->color.y);
	final_color.y = ray_data.color.y;
	ray_data.color = final_color;
	return (ray_data);
}

void	render_glass(t_env *env, t_ray_d *l_ray)
{
	t_ray_d	ray_data;
	t_ray_d	ray_reflect;
	float	dot;

	ft_memset(&ray_reflect, 0, sizeof(t_ray_d));
	ray_reflect.ray.dir = normalize(reflect(l_ray->ray.dir, l_ray->n, .05));
	ray_reflect.ray.origin = l_ray->hp;
	ray_data = render_ior(env, l_ray);
	dot = fabs(vec_dot(l_ray->ray.dir, l_ray->n));
	ray_reflect = get_pixel_color(env, ray_reflect.ray, NULL);
	*l_ray = ray_data;
	if (dot < .1)
		dot = .1;
	l_ray->color = vec_add(vec_mul(l_ray->color, dot), \
			vec_mul(ray_reflect.color, 1 - dot));
	l_ray->glass_flag = 0;
}
