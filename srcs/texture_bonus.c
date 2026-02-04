/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 08:03:01 by nlaporte          #+#    #+#             */
/*   Updated: 2026/02/04 19:53:59 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../lib/mlx/mlx.h"
#include <X11/Xlib.h>
#include <X11/extensions/XShm.h>
#include <stddef.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

char	*get_path(char *str, int line)
{
	char	**path_split;

	if (!str)
		return (NULL);
	if (ft_strrchr(str, '/'))
		path_split = ft_split(ft_strrchr(str, '/'), '.');
	else
		path_split = ft_split(str, '.');
	if (!path_split || !path_split[0] || !path_split[1] || path_split[2])
	{
		printf("Error (line %i): Bad name\n", line);
		if (path_split)
			return (ft_free_split(path_split), NULL);
		return (NULL);
	}
	if (ft_strcmp(path_split[1], "xpm") != 0 || ft_strlen(path_split[1]) != 3)
	{
		printf("Error (line %i): Bad extension need .xpm\n", line);
		ft_free_split(path_split);
		return (NULL);
	}
	ft_free_split(path_split);
	return (ft_strndup(str, ft_strlen(str)));
}

int	load_img_texture(t_env *env, char *split, t_texture *texture, int line)
{
	char	*path;

	path = get_path(split, line);
	if (!path)
		return (1);
	texture->img = mlx_xpm_file_to_image(env->mlx, path, \
			&texture->w, &texture->h);
	if (!texture->img)
	{
		printf("Error (line %i) Can't import texture\n", line);
		free(path);
		return (1);
	}
	free(path);
	texture->buf = mlx_get_data_addr(texture->img, &texture->bpp, \
			&texture->lb, &texture->endian);
	if (!texture->buf)
	{
		printf("Error (line %i): Can't load texture\n", line);
		return (1);
	}
	texture->mlx = env;
	return (0);
}

int	load_img_texture_normal(t_env *env, t_texture *texture, \
	char *split, int line)
{
	char	*path;

	path = get_path(split, line);
	if (!path)
		return (1);
	texture->img_n = NULL;
	texture->buf_n = NULL;
	texture->img_n = mlx_xpm_file_to_image(env->mlx, path, \
			&texture->w, &texture->h);
	if (!texture->img_n)
	{
		printf("Error (line %i): Can't import normal map\n", line);
		free(path);
		return (1);
	}
	free(path);
	texture->buf_n = mlx_get_data_addr(texture->img_n, \
			&texture->bpp, &texture->lb, &texture->endian);
	if (!texture->buf_n)
	{
		printf("Error (line %i): Can't load normal map\n", line);
		return (1);
	}
	return (0);
}

int	load_minimal(t_texture *texture, \
		char *values[], char *id)
{
	float	reflect;
	float	roug;
	char	*id_text;

	ft_memset(texture, 0, sizeof(t_texture));
	id_text = ft_strndup(id, ft_strlen(id));
	if (!id_text)
		return (1);
	reflect = fmin(1, fmax(0, ft_atof(values[0])));
	roug = fmin(1, fmax(0, ft_atof(values[1])));
	texture->name = id_text;
	texture->reflection = reflect;
	texture->rougness = roug;
	texture->img = NULL;
	texture->img_n = NULL;
	return (0);
}

int	create_texture(t_env *env, char **split, int line)
{
	t_texture	*texture_p;

	if (!split[0] || !split[1] || !split[2] || !split[3])
		return (printf("Error (line %i): texture need 3 args\n", line), 1);
	if (find_texture(env, split[3]) || ft_strncmp(split[3], "glass", 5) == 0 \
			|| ft_strncmp(split[3], "checkboard", 10) == 0)
		return (printf("Error (line %i): texture id already used \
(glass and checkboard is used by default)\n", line), 1);
	texture_p = malloc(sizeof(t_texture));
	if (!texture_p)
		return (printf("Cant malloc\n"), 1);
	if (load_minimal(texture_p, (char *[2]){split[1], split[2]}, split[3]))
		return (printf("Error (line %i): Can't malloc\n", line), \
				free(texture_p), 1);
	if (!split[4])
		return (ft_lstadd_back(&env->scene.textures, ft_lstnew(texture_p)), 0);
	if (load_img_texture(env, split[4], texture_p, line))
		return (free_texture(texture_p), 1);
	if (!split[5])
		return (ft_lstadd_back(&env->scene.textures, ft_lstnew(texture_p)), 0);
	if (load_img_texture_normal(env, texture_p, split[5], line))
		return (free_texture(texture_p), 1);
	pthread_mutex_init(&texture_p->text_mutex, NULL);
	return (ft_lstadd_back(&env->scene.textures, ft_lstnew(texture_p)), 0);
}
