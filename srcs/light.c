/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 16:57:04 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/23 11:22:35 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <iso646.h>
#include <math.h>
#include <limits.h>
#include <float.h>

/**
 * @brief get_specular_light
 *
 * Calcule la lumiere speculaire
 *
 * R = 2 * vec_dot(Normal, Light dir) Normal - Light dir
 * speculaire = powf(R*V, [1-1000])
 *
 * @param t_light lightr
 * @param t_vec3 light_dir
 * @param t_ray_d ray
 *
 * @return float specular ligh intensityt
 */
float	get_specular_light(t_vec3 light_dir, t_ray_d ray)
{
	t_vec3	v_reflect;
	t_vec3	r;
	float	dot;

	dot = 2 * (ray.n.x * light_dir.x + ray.n.y * \
			light_dir.y + ray.n.z * light_dir.z);
	r.x = dot * ray.n.x - light_dir.x;
	r.y = dot * ray.n.y - light_dir.y;
	r.z = dot * ray.n.z - light_dir.z;
	v_reflect = normalize(r);
	dot = v_reflect.x * ray.ray.dir.x + \
	v_reflect.y * ray.ray.dir.y + v_reflect.z * ray.ray.dir.z;
	if (dot < 0.)
		return (fabs(powf(dot, 7.)) * SPECULAR_COEF);
	return (0.);
}

/**
 * @brief light_is_hide
 *
 * Verifie si la lumiere est bloquer
 * par un object
 *
 * @param t_env *env
 * @param t_scene *scene 
 * @param t_vec3 origin 
 * @param t_vec3 light_dir 
 * @param t_vec3 light_pos;
 * @return int 
 */
int	light_is_hide(t_env *env, t_vec3 origin, \
		t_vec3 light_dir, t_vec3 light_pos)
{
	t_ray	ray;
	t_ray_d	n;
	float	light_dist;

	ft_memset(&ray, 0, sizeof(t_ray));
	ft_memset(&n, 0, sizeof(t_ray_d));
	ray.origin = vec_add(origin, vec_mul(light_dir, EPS));
	ray.dir = normalize(vec_sub(light_pos, origin));
	light_dist = vec_length(ray.dir);
	n = check_all_objects(env, ray, NULL, 0);
	if (n.t > EPS && n.t <= light_dist && !n.glass_flag)
		return (1);
	return (0);
}

/**
 * @brief 
 * 
 * Calcule l'intensite lumineuse difuse 
 * et speculaire
 *
 * difuse = vec_dot(Normal, Light dir)
 *
 * @param t_env *env
 * @param t_scene *scene
 * @param t_light *light 
 * @param t_ray_d ray 
 * @return 
 */
float	get_light_intensity(t_env *env, \
		t_light *light, t_ray_d ray)
{
	float	r;
	float	dot;
	t_vec3	light_dir;

	light_dir = (t_vec3){light->pos.x - ray.hp.x, \
	light->pos.y - ray.hp.y, light->pos.z - ray.hp.z};
	light_dir = normalize(light_dir);
	dot = light_dir.x * ray.n.x + light_dir.y * ray.n.y + light_dir.z * ray.n.z;
	if (dot <= 0.)
		return (0.);
	dot = fmin(dot, 1);
	if (light_is_hide(env, ray.hp, light_dir, light->pos) && ray.t < 20000)
		return (0.);
	r = (fmin(1., fmax(0, dot * light->brightness)));
	r += get_specular_light(light_dir, ray);
	return (fmin(.9, r));
}

/**
 * @brief 
 * 
 * Retourne la quantite de lumiere sur un point
 *
 * @param t_scene *scene
 * @param t_scene *scene
 * @param t_ray_d ray
 * @return t_vec3 final_color
 */
t_vec3	check_all_light(t_env *env, t_scene *scene, t_ray_d ray)
{
	t_list	*lights;
	t_light	*light;
	t_vec3	light_color;
	float	brightness;

	lights = scene->lights;
	light_color.x = scene->amb_light.brightness * scene->amb_light.color.x;
	light_color.y = scene->amb_light.brightness * scene->amb_light.color.y;
	light_color.z = scene->amb_light.brightness * scene->amb_light.color.z;
	while (lights)
	{
		light = lights->content;
		lights = lights->next;
		brightness = get_light_intensity(env, light, ray);
		light_color.x += brightness * light->color.x;
		light_color.y += brightness * light->color.y;
		light_color.z += brightness * light->color.z;
	}
	return (light_color);
}
