/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 20:30:28 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/22 07:07:32 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/libft/libft.h"
#include <X11/Xlib.h>
#include <X11/extensions/XShm.h>
#include "../minirt.h"
#include <float.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <math.h>

/**
 * @brief create_sphere
 *
 * Creer un nouvel object sphere depuis le parsing
 *
 *
 * @param t_env *env 
 * @param char **split 
 * @param int line 
 * @return int code
 */
int	create_sphere(t_env *env, char **split, int line)
{
	t_sphere	sphere;
	t_sphere	*sphere_p;

	if (!split || !split[1] || !split[2] || !split[3])
		return (printf("Error (line %i): Bad args\n", line), 1);
	ft_memset(&sphere, 0, sizeof(t_sphere));
	if (parse_vector_float(split[1], &sphere.pos, \
			(float [2]){-9999999., 9999999.}, line))
		return (1);
	if (parse_vector_float(split[3], &sphere.color, (float [2]){0, 255}, line))
		return (1);
	if (split[4] && add_sphere_texture(env, split, &sphere, line))
		return (1);
	sphere.type = SPHERE;
	sphere.r = ft_atof(split[2]);
	sphere.q = identity_q();
	sphere_p = malloc(sizeof(t_sphere));
	if (!sphere_p)
		return (1);
	ft_memcpy(sphere_p, &sphere, sizeof(t_sphere));
	ft_lstadd_back(&env->scene.spheres, ft_lstnew(sphere_p));
	return (0);
}

/**
 * @brief create_plane
 *
 * Creer un nouvel object plan depuis le parsing
 *
 * @param t_env *env 
 * @param char **split 
 * @param int line 
 * @return int code
 */
int	create_plane(t_env *env, char **split, int line)
{
	t_plane	plane;
	t_plane	*plane_p;

	if (!split || !split[1] || !split[2] || !split[3])
		return (printf("Error (line %i): Bad args\n", line), 1);
	ft_memset(&plane, 0, sizeof(t_plane));
	if (parse_vector_float(split[1], &plane.pos, \
			(float [2]){-9999999., 9999999.}, line))
		return (1);
	if (parse_vector_float(split[2], &plane.n, \
			(float [2]){-1., 1.}, line))
		return (1);
	if (parse_vector_float(split[3], &plane.color, (float [2]){0, 255.}, line))
		return (1);
	if (split[4] && add_plane_texture(env, split, &plane, line))
		return (1);
	plane.type = PLANE;
	plane.q = quat_from_to((t_vec3){0, 1, 0}, plane.n);
	plane_p = malloc(sizeof(t_plane));
	if (!plane_p)
		return (perror("Error"), 1);
	ft_memcpy(plane_p, &plane, sizeof(t_plane));
	ft_lstadd_back(&env->scene.planes, ft_lstnew(plane_p));
	return (0);
}

/**
 * @brief create_cylinder
 *
 * Creer un nouvel object cylindre depuis le parsing
 *
 * @param t_env *env 
 * @param char **split 
 * @param int line 
 * @return int code
 */
int	create_cylinder(t_env *env, char **split, int line)
{
	t_cylinder	cy;
	t_cylinder	*cy_p;

	if (!split || !split[1] || !split[2] || !split[3] || !split[4] || !split[5])
		return (printf("Error (line %i): Bad args\n", line), 1);
	ft_memset(&cy, 0, sizeof(t_cylinder));
	if (parse_vector_float(split[1], &cy.pos, \
			(float [2]){-9999999., 9999999.}, line))
		return (1);
	if (parse_vector_float(split[2], &cy.axis, (float [2]){-1., 1.}, line))
		return (1);
	if (parse_vector_float(split[5], &cy.color, (float [2]){0, 255}, line))
		return (1);
	if (split[6] && ft_strncmp(split[6], "glass", 5) == 0)
		cy.glass_flag = 1;
	if (split[6] && add_cyl_texture(env, split, &cy, line))
		return (1);
	init_cylinder(&cy, split);
	cy_p = malloc(sizeof(t_cylinder));
	if (!cy_p)
		return (perror("Error"), 1);
	ft_memcpy(cy_p, &cy, sizeof(t_cylinder));
	ft_lstadd_back(&env->scene.cylinders, ft_lstnew(cy_p));
	return (0);
}

/**
 * @brief create_cone
 *
 * Creer un nouvel object cone depuis le parsing
 *
 * @param t_env *env 
 * @param char **split 
 * @param int line 
 * @return int code
 */
int	create_cone(t_env *env, char **split, int line)
{
	t_cone	cone;
	t_cone	*cone_p;

	ft_memset(&cone, 0, sizeof(t_cone));
	if (!split || !split[1] || !split[2] || !split[3] || !split[4] || !split[5])
		return (printf("Error (line %i): Bad args\n", line), 1);
	if (parse_vector_float(split[1], &cone.pos, \
			(float [2]){-9999999., 9999999.}, line))
		return (1);
	if (parse_vector_float(split[2], &cone.axis, \
			(float [2]){-1., 1.}, line))
		return (1);
	if (parse_vector_float(split[5], &cone.color, \
			(float [2]){0, 255}, line))
		return (1);
	if (split[6] && add_cone_texture(env, split, &cone, line))
		return (1);
	init_cone(&cone, split);
	cone_p = malloc(sizeof(t_cylinder));
	if (!cone_p)
		return (perror("Error"), 1);
	ft_memcpy(cone_p, &cone, sizeof(t_cylinder));
	ft_lstadd_back(&env->scene.cones, ft_lstnew(cone_p));
	return (0);
}
