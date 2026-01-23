/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 16:05:08 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/21 20:32:18 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"
#include <stdio.h>

/**
 * @brief find_texture
 *
 * Retourne la texture correspondant a l'id ou NULL
 *
 * @param t_env *env
 * @param char *s 
 *
 * @return t_texture *text
 */
t_texture	*find_texture(t_env *env, char *s)
{
	t_list		*texts;
	t_texture	*text;

	texts = env->scene.textures;
	while (texts)
	{
		text = texts->content;
		if (!ft_strcmp(s, text->name) && ft_strlen(s) == ft_strlen(text->name))
			return (text);
		texts = texts->next;
	}
	return (NULL);
}

/**
 * @brief add_sphere_texture
 *
 * Ajout la texture correct a la sphere
 * ou retorune une erreur
 *
 * @param t_env *env 
 * @param char **split 
 * @param t_sphere *sphere
 * @param int line 
 * @return int code 
 */
int	add_sphere_texture(t_env *env, char **split, t_sphere *sphere, int line)
{
	if (ft_strncmp(split[4], "glass", 6) == 0)
		sphere->glass_flag = 1;
	else if (ft_strncmp(split[4], "checkboard", 11) == 0)
		sphere->checkboard_flag = 1;
	else if (ft_strncmp(split[4], "pal1", 4) == 0)
		return (sphere->pal_flag = 1, sphere->pal = palette1, 0);
	else if (ft_strncmp(split[4], "pal2", 4) == 0)
		return (sphere->pal_flag = 1, sphere->pal = palette2, 0);
	else if (ft_strncmp(split[4], "pal3", 4) == 0)
		return (sphere->pal_flag = 1, sphere->pal = palette3, 0);
	else if (ft_strncmp(split[4], "pal4", 4) == 0)
		return (sphere->pal_flag = 1, sphere->pal = palette4, 0);
	else
	{
		sphere->texture = find_texture(env, split[4]);
		if (!sphere->texture)
			return (printf("Error (line %i): Bad texture id\n", line), 1);
	}
	return (0);
}

/**
 * @brief add_plane_texture
 *
 * Ajout la texture correct au plan
 * ou retorune une erreur
 *
 * @param t_env *env 
 * @param char **split 
 * @param t_plane *plane 
 * @param int line 
 * @return int code 
 */
int	add_plane_texture(t_env *env, char **split, t_plane *plane, int line)
{
	if (ft_strncmp(split[4], "glass", 6) == 0)
		plane->glass_flag = 1;
	else if (ft_strncmp(split[4], "checkboard", 6) == 0)
		plane->checkboard_flag = 1;
	else if (ft_strncmp(split[4], "pal1", 4) == 0)
		return (plane->pal_flag = 1, plane->pal = palette1, 0);
	else if (ft_strncmp(split[4], "pal2", 4) == 0)
		return (plane->pal_flag = 1, plane->pal = palette2, 0);
	else if (ft_strncmp(split[4], "pal3", 4) == 0)
		return (plane->pal_flag = 1, plane->pal = palette3, 0);
	else if (ft_strncmp(split[4], "pal4", 4) == 0)
		return (plane->pal_flag = 1, plane->pal = palette4, 0);
	else
	{
		plane->texture = find_texture(env, split[4]);
		if (!plane->texture)
			return (printf("Error (line %i): Bad texture id\n", line), 1);
	}
	return (0);
}

int	add_cyl_texture(t_env *env, char **split, t_cylinder *cyl, int line)
{
	if (ft_strncmp(split[6], "glass", 6) == 0)
		cyl->glass_flag = 1;
	else if (ft_strncmp(split[6], "checkboard", 6) == 0)
		cyl->checkboard_flag = 1;
	else if (ft_strncmp(split[6], "pal1", 4) == 0)
		return (cyl->pal_flag = 1, cyl->pal = palette1, 0);
	else if (ft_strncmp(split[6], "pal2", 4) == 0)
		return (cyl->pal_flag = 1, cyl->pal = palette2, 0);
	else if (ft_strncmp(split[6], "pal3", 4) == 0)
		return (cyl->pal_flag = 1, cyl->pal = palette3, 0);
	else if (ft_strncmp(split[6], "pal4", 4) == 0)
		return (cyl->pal_flag = 1, cyl->pal = palette4, 0);
	else
	{
		cyl->texture = find_texture(env, split[6]);
		if (!cyl->texture)
			return (printf("Error (line %i): Bad texture id\n", line), 1);
	}
	return (0);
}

int	add_cone_texture(t_env *env, char **split, t_cone *cone, int line)
{
	if (ft_strncmp(split[6], "glass", 6) == 0)
		cone->glass_flag = 1;
	else if (ft_strncmp(split[6], "checkboard", 6) == 0)
		cone->checkboard_flag = 1;
	else if (ft_strncmp(split[6], "pal1", 4) == 0)
		return (cone->pal_flag = 1, cone->pal = palette1, 0);
	else if (ft_strncmp(split[6], "pal2", 4) == 0)
		return (cone->pal_flag = 1, cone->pal = palette2, 0);
	else if (ft_strncmp(split[6], "pal3", 4) == 0)
		return (cone->pal_flag = 1, cone->pal = palette3, 0);
	else if (ft_strncmp(split[6], "pal4", 4) == 0)
		return (cone->pal_flag = 1, cone->pal = palette4, 0);
	else
	{
		cone->texture = find_texture(env, split[6]);
		if (!cone->texture)
			return (printf("Error (line %i): Bad texture id\n", line), 1);
	}
	return (0);
}
