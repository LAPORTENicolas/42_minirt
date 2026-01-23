/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 22:35:00 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/23 12:48:14 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include "../minirt.h"
#include <float.h>
#include <stdio.h>
#include <math.h>

/**
 * @brief create_amb_light
 *
 * Parsing lumiere ambiante depuis le fichier scene
 *
 * @param t_env *env 
 * @param char **split 
 * @param t_parsing *parsing 
 * @return code
 */
int	create_amb_light(t_env *env, char **split, t_parsing *parsing)
{
	if (parsing->amb_light_bool || !split[0] || !split[1] \
			|| !split[2] || split[3])
	{
		if (parsing->amb_light_bool)
			printf("Error (line %i): only one ambient \
					light needed\n", parsing->line);
		else
			printf("Error (line %i): for ambient light \
					need color and brightness\n", parsing->line);
		return (-1);
	}
	if (parse_vector_float(split[2], &env->scene.amb_light.color, \
				(float [2]){0, 255}, parsing->line))
		return (-1);
	env->scene.amb_light.color.x /= 255;
	env->scene.amb_light.color.y /= 255;
	env->scene.amb_light.color.z /= 255;
	env->scene.amb_light.brightness = ft_atof(split[1]);
	parsing->amb_light_bool = 1;
	return (0);
}

/**
 * @brief create_light
 *
 * Parsing lumiere depuis le fichier scene
 *
 * @param t_env *env 
 * @param char **split 
 * @param t_parsing *parsing 
 * @return code
 */
int	create_light(t_env *env, char **split, t_parsing *parsing)
{
	t_light	light;
	t_light	*light_p;

	if (!split[0] || !split[1] || !split[2] || !split[3])
		return (printf("Error (line %i): for light need color, \
					position and brightness\n", parsing->line), -1);
	if (parse_vector_float(split[1], &light.pos, \
			(float [2]){-99999, 99999}, parsing->line))
		return (-1);
	if (parse_vector_float(split[3], &light.color, \
				(float [2]){0., 255.}, parsing->line))
		return (-1);
	light.color.x /= 255;
	light.color.y /= 255;
	light.color.z /= 255;
	light.brightness = ft_atof(split[2]);
	light_p = malloc(sizeof(t_light));
	if (!light_p)
		return (perror("Error"), -1);
	ft_memcpy(light_p, &light, sizeof(t_light));
	ft_lstadd_back(&env->scene.lights, ft_lstnew(light_p));
	parsing->light_bool = 1;
	return (0);
}

/**
 * @brief create_camera
 *
 * Parsing camera depuis le fichier scene
 *
 * @param t_env *env 
 * @param char **split 
 * @param t_parsing *parsing 
 * @return code
 */

int	create_camera(t_env *env, char **split, t_parsing *parsing)
{
	if (parsing->cam_bool || !split[0] || !split[1] || !split[2] \
		|| !split[3])
	{
		if (parsing->cam_bool)
			return (printf("Error (line %i): only one camera needed\n", \
						parsing->line), -1);
		return (printf("Error (line %i): for camera need position, normalized direction \
			and field of view\n", parsing->line), -1);
	}
	if (parse_vector_float(split[1], &env->camera.pos, \
				(float [2]){-999, 999.}, parsing->line))
		return (1);
	if (parse_vector_float(split[2], &env->camera.forward, \
				(float [2]){-999, 999.}, parsing->line))
		return (1);
	env->camera.fov = ft_atof(split[3]);
	if (env->camera.fov <= 10 || env->camera.fov >= 120)
		return (printf("Error 11 >= fov <= 120 \n"), 1);
	define_worldup(&env->camera.world_up, env->camera.forward);
	env->camera.right = normalize(vec_cross(env->camera.world_up, \
				env->camera.forward));
	env->camera.up = normalize(vec_cross(env->camera.forward, \
				env->camera.right));
	parsing->cam_bool = 1;
	copy_origin_cam(env);
	return (0);
}
