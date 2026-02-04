/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:03:56 by nlaporte          #+#    #+#             */
/*   Updated: 2026/02/04 20:13:41 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/mlx/mlx.h"
#include "minirt.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief init_img
 *
 * Initialise l'image de rendu
 * de la mlx
 * Si return different de 0, erreur lors de la 
 * l'init, ferme proprement la mlx
 *
 * @param t_env *env
 * @param int width
 * @param int height
 *
 * @return int
 */
int	init_img(t_env *env, int width, int height)
{
	env->win.img = mlx_new_image(env->mlx, width, height);
	if (!env->win.img)
		return (1);
	env->win.buf = mlx_get_data_addr(env->win.img, &env->win.bpp, \
			&env->win.lb, &env->win.endian);
	if (!env->win.buf)
	{
		printf("Can't create image data\n");
		mlx_destroy_image(env->mlx, env->win.img);
		mlx_destroy_window(env->mlx, env->win.win);
		mlx_destroy_display(env->mlx);
		free(env->win.img_buf_render);
		free(env->mlx);
		free(env->win.img_buf);
		return (2);
	}
	return (0);
}

/**
 * @brief init_mlx
 *
 * Init la mlx et la fenetre de rendu
 *
 * @param t_env *env 
 * @param int width 
 * @param int height 
 * @return int code
 */
int	init_mlx(t_env *env, int width, int height)
{
	env->mlx = mlx_init();
	if (!env->mlx)
	{
		free(env->win.img_buf);
		free(env->win.img_buf_render);
		printf("Can't init minilibx\n");
		return (1);
	}
	env->win.win = mlx_new_window(env->mlx, width, height, "Minirt");
	if (!env->win.win)
	{
		printf("Can't create window\n");
		mlx_destroy_display(env->mlx);
		free(env->mlx);
		free(env->win.img_buf);
		free(env->win.img_buf_render);
		return (2);
	}
	return (0);
}

/**
 * @brief init_win
 *
 * Initialise la mlx, creer fenetre et image
 * Si return different de 0, erreur lors de la 
 * l'init, ferme proprement la mlx
 *
 * @param t_env *env
 * @param int width
 * @param int height
 *
 * @return int
 */
int	init_win(t_env *env, int width, int height)
{
	env->win.width = width;
	env->win.height = height;
	env->size = width * height;
	env->win.img_buf_render = malloc(sizeof(t_vec3) * WIDTH * HEIGHT);
	if (!env->win.img_buf_render)
	{
		printf("Can't create image buf render\n");
		return (1);
	}
	env->win.img_buf = malloc(sizeof(t_vec3) * WIDTH * HEIGHT);
	if (!env->win.img_buf)
	{
		printf("Can't create image buf\n");
		free(env->win.img_buf_render);
		env->win.img_buf_render = NULL;
		env->win.img_buf = NULL;
		return (1);
	}
	if (init_mlx(env, width, height))
		return (1);
	return (init_img(env, width, height));
}

/**
 * @brief exit_mlx
 *
 * Quitte proprement la mlx
 *
 * @param t_env *env
 *
 */
void	exit_mlx(t_env *env)
{
	if (env->win.img)
		mlx_destroy_image(env->mlx, env->win.img);
	if (env->win.win)
		mlx_destroy_window(env->mlx, env->win.win);
	if (env->mlx)
		mlx_destroy_display(env->mlx);
	if (env->file)
		free(env->file);
	if (env->win.img_buf)
		free(env->win.img_buf);
	if (env->win.img_buf_render)
		free(env->win.img_buf_render);
	free_lists(env);
	if (env->mlx)
		free(env->mlx);
	join_threads(env);
	exit(0);
}
