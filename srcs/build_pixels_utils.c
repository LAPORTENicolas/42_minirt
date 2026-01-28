/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_pixels_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:06:05 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/28 06:47:54 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <limits.h>
#include <float.h>

/**
 * @brief reflect
 *
 * Pour un rayon calcul le rayon reflechi
 * en fonction de la roughness
 *
 * @param t_vec3 I 
 * @param t_vec3 N 
 * @param float rougness 
 * @return t_vec3 r
 */
t_vec3	reflect(t_vec3 I, t_vec3 N, float rougness)
{
	t_vec3	r;
	float	dot;

	dot = N.x * I.x + N.y * I.y + N.z * I.z;
	if (rougness != 0)
	{
		r.x = fmin(1, fmax(-1, \
		(I.x - 2. * dot * N.x) + ((fmod(rand() * 1e-2, 2) - 1.) * rougness)));
		r.y = fmin(1, fmax(-1, \
		(I.y - 2. * dot * N.y) + ((fmod(rand() * 1e-2, 2) - 1.) * rougness)));
		r.z = fmin(1, fmax(-1, \
		(I.z - 2. * dot * N.z) + ((fmod(rand() * 1e-2, 2) - 1.) * rougness)));
	}
	else
	{
		r.x = (I.x - 2. * dot * N.x);
		r.y = (I.y - 2. * dot * N.y);
		r.z = (I.z - 2. * dot * N.z);
	}
	return (r);
}

/**
 * @brief refract
 *
 * Refract un rayon en fonction de la normal et 
 * d'un coef de refraction
 *
 * @param t_vec3 I 
 * @param t_vec3 N 
 * @param float eta
 * @return t_vec3 r
 */
t_vec3	refract(t_vec3 I, t_vec3 N, float eta)
{
	float	dot_ni;
	float	sqrt_k;
	float	k;

	I = normalize(I);
	N = normalize(N);
	dot_ni = fabs(vec_dot(N, I));
	k = 1. - eta * eta * (1. - dot_ni * dot_ni);
	if (k < 0)
		return ((t_vec3){0, 0, 0});
	sqrt_k = sqrtf(k);
	dot_ni = eta * dot_ni + sqrt_k;
	return ((t_vec3){
		eta * I.x - dot_ni * N.x,
		eta * I.y - dot_ni * N.y,
		eta * I.z - dot_ni * N.z,
	});
}

/**
 * @brief get_random_vec
 *
 * Retourne un vecteur "aleatoire"
 * dans le fourchette -dispertion <= N <= dispertion
 *
 * @param float dispertion 
 * @return t_vec3 r
 */
t_vec3	get_random_vec(float dispertion)
{
	t_vec3	r;

	r.x = (fmod(rand() * 1e-2, 2) - 1.) * dispertion;
	r.y = (fmod(rand() * 1e-2, 2) - 1.) * dispertion;
	r.z = (fmod(rand() * 1e-2, 2) - 1.) * dispertion;
	return (r);
}

/**
 * @brief	get_pixel_color
 *
 * Recuperer l'intersection la plus proche
 * pour retourner la couleur a afficher
 * a partir d'un rayon
 *
 * @param t_env *env
 * @param t_ray ray
 *
 * @return t_vec3 color

 */
t_ray_d	get_pixel_color(t_env *env, t_ray ray, void *last)
{
	t_ray_d		most_short;
	t_vec3		light_intensity;

	ft_memset(&most_short, 0, sizeof(t_ray_d));
	most_short = check_all_objects(env, ray, last, 0);
	if (most_short.t != FLT_MAX)
	{
		light_intensity = check_all_light(env, &env->scene, most_short);
		most_short.color.x *= light_intensity.x;
		most_short.color.y *= light_intensity.y;
		most_short.color.z *= light_intensity.z;
	}
	return (most_short);
}
