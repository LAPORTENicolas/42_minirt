/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils _bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:59:50 by nlaporte          #+#    #+#             */
/*   Updated: 2026/02/05 10:56:53 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief put_pixel
 *
 * Definit la couleur d'un pixel dans l'image temporaire generer
 * de rendu de la mlx
 *
 * @param t_env *env
 * @param t_vec3 color {r, g, b}
 * @param int pixel index
 *
 */
void	put_pixel(t_env *env, t_vec3 color, int i)
{
	pthread_mutex_lock(&env->win_mutex);
	env->win.img_buf[i].x = color.x;
	env->win.img_buf[i].y = color.y;
	env->win.img_buf[i].z = color.z;
	pthread_mutex_unlock(&env->win_mutex);
}

void	put_pixel_in_render2(t_env *env)
{
	int	i;
	int	size;
	int	x;
	int	y;

	i = 0;
	size = WIDTH * HEIGHT;
	while (i < size)
	{
		x = (i % WIDTH) / SCALE;
		y = (i / WIDTH) / SCALE;
		env->win.img_buf_render[i].x += \
		env->win.img_buf[x + (WIDTH / SCALE) * y].x;
		env->win.img_buf_render[i].y += \
		env->win.img_buf[x + (WIDTH / SCALE) * y].y;
		env->win.img_buf_render[i].z += \
		env->win.img_buf[x + (WIDTH / SCALE) * y].z;
		i++;
	}
}

/**
 * @brief put_img_buf_to_img_render
 *
 * Ajout l'image temporaire dans limage de rendu
 * de rendu de la mlx
 *
 * @param t_env *env
 *
 */
void	put_pixel_in_render(t_env *env)
{
	int	i;
	int	size;

	if (env->litle_resolution)
		return (put_pixel_in_render2(env));
	i = 0;
	size = WIDTH * HEIGHT;
	while (i < size)
	{
		env->win.img_buf_render[i].x += env->win.img_buf[i].x;
		env->win.img_buf_render[i].y += env->win.img_buf[i].y;
		env->win.img_buf_render[i].z += env->win.img_buf[i].z;
		i++;
	}
}

static inline unsigned char	clamp_uc(float v)
{
	if (v < 0.0f)
		return (0);
	if (v > 255.0f)
		return (255);
	return ((unsigned char)(v));
}

/**
 * @brief put_buffer_to_mlx
 *
 * Ajout limage dans le buffer de la mlx avant affichage
 * anti crenelage temporelle en fonction de render_amount
 * fait la moyen des couleur pour un pixel
 *
 * @param t_win *win 
 * @param int render_amount 
 */
void	put_buffer_to_mlx(t_win *win, int render_amount)
{
	int	i;
	int	size;

	i = 0;
	size = HEIGHT * WIDTH;
	while (i < size)
	{
		win->buf[i << 2] = clamp_uc(win->img_buf_render[i].z / \
			render_amount);
		win->buf[(i << 2) + 1] = clamp_uc(win->img_buf_render[i].y / \
			render_amount);
		win->buf[(i << 2) + 2] = clamp_uc(win->img_buf_render[i].x / \
			render_amount);
		i++;
	}
}
