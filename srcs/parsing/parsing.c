/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 17:43:44 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/20 03:26:05 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/gnl/get_next_line.h"
#include "../../lib/libft/libft.h"
#include "../minirt.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

/**
 * @brief get_obj_type
 *
 * Retourne le type d'object
 *
 * @param char *s 
 * @return int type
 */
int	get_obj_type(char *s)
{
	if (s[0] == 'A' && s[1] == 0)
		return (AMB_LIGHT);
	else if (s[0] == 'C' && s[1] == 0)
		return (CAMERA);
	else if (s[0] == 'L' && s[1] == 0)
		return (LIGHT);
	else if (s[0] == 's' && s[1] == 'p' && s[2] == 0)
		return (SPHERE);
	else if (s[0] == 'p' && s[1] == 'l' && s[2] == 0)
		return (PLANE);
	else if (s[0] == 'c' && s[1] == 'y' && s[2] == 0)
		return (CYLINDER);
	else if (s[0] == 'c' && s[1] == 'o' && s[2] == 0)
		return (CONE);
	else if (s[0] == 't' && s[1] == 'e' && s[2] == 0)
		return (TEXTURE);
	return (-1);
}

int	create_from_parsing(t_env *env, char **split, \
		t_parsing *parsing, t_obj_type obj_type)
{
	int	code;

	code = 0;
	if (obj_type == AMB_LIGHT)
		code = create_amb_light(env, split, parsing);
	else if (obj_type == CAMERA)
		code = create_camera(env, split, parsing);
	else if (obj_type == LIGHT)
		code = create_light(env, split, parsing);
	else if (obj_type == SPHERE)
		code = create_sphere(env, split, parsing->line);
	else if (obj_type == PLANE)
		code = create_plane(env, split, parsing->line);
	else if (obj_type == CYLINDER)
		code = create_cylinder(env, split, parsing->line);
	else if (obj_type == CONE)
		code = create_cone(env, split, parsing->line);
	else if (obj_type == TEXTURE)
		code = create_texture(env, split, parsing->line);
	return (code);
}

/**
 * @brief parse_line
 *
 * Redirige vers la fonction de creation d'objet
 *
 * @param t_env *env 
 * @param char *s 
 * @param t_parsing parsing 
 * @return int code
 */
int	parse_line(t_env *env, char *s, t_parsing *parsing)
{
	char	**split;
	int		obj_type;
	int		code;

	while (ft_isspace(*s))
		s++;
	if (!s || !*s || *s == '#')
		return (0);
	split = ft_split(s, ' ');
	if (!split)
		return (-1);
	obj_type = get_obj_type(split[0]);
	code = 0;
	if (obj_type == -1)
		return (printf("Error (line %i): bad identifier\n", \
				parsing->line), ft_free_split(split), -2);
	else
		code = create_from_parsing(env, split, parsing, obj_type);
	ft_free_split(split);
	return (code);
}

/**
 * @brief check_min_obj
 *
 * verifie les objects necessaire pour une scene
 *
 * @param t_parsing parsing 
 * @return int code
 */
int	check_min_obj(t_parsing parsing)
{
	if (!parsing.amb_light_bool)
	{
		printf("Error: valid scene need ambient light\n");
		return (1);
	}
	if (!parsing.light_bool)
	{
		printf("Error: valid scene need light\n");
		return (1);
	}
	if (!parsing.cam_bool)
	{
		printf("Error: valid scene need camera\n");
		return (1);
	}
	return (0);
}

/**
 * @brief prepare_parsing
 *
 * Ouvre le fichier de scene et le parse
 *
 * @param t_env *env 
 * @return int code
 */
int	prepare_parsing(t_env *env, char *file)
{
	t_parsing	parsing;
	char		*s;
	char		*p;

	ft_memset(&parsing, 0, sizeof(t_parsing));
	parsing.fd = open(file, O_RDONLY);
	if (parsing.fd <= 0)
	{
		printf("Error: can't open %s %s", file, strerror(errno));
		return (-1);
	}
	s = get_next_line(parsing.fd);
	while (s)
	{
		p = ft_strchr(s, '\n');
		if (p)
			*p = 0;
		if (parse_line(env, s, &parsing))
			return (free(s), 1);
		free(s);
		s = get_next_line(parsing.fd);
		parsing.line++;
	}
	close(parsing.fd);
	return (check_min_obj(parsing));
}
