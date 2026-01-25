/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:08:21 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/25 02:37:58 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <X11/X.h>
#include <X11/keysymdef.h>

void	change_screen_mode(t_env *env)
{
	if (env->screen_mode == CAMERA_MODE)
		env->screen_mode = EDIT_MODE;
	else
		env->screen_mode = CAMERA_MODE;
}

int	mvt_keys(int key)
{
	return (key == W_KEY || key == S_KEY || key == A_KEY || key == D_KEY || \
			key == E_KEY || key == Q_KEY || key == Z_KEY || key == C_KEY || \
			key == UP_KEY || key == DOWN_KEY || key == LEFT_KEY);
}

void	keyboard_release(int key, t_env *env)
{
	if (key == Z_KEY)
		env->z_key_pressed = 0;
}

void	keyboard_hook_part2(int key, t_env *env)
{
	if (key == R_KEY && env->screen_mode == EDIT_MODE && \
			env->selected_obj != NO_OBJ)
	{
		restore_obj(env, env->obj);
		env->selected_obj = NO_OBJ;
		env->win.need_reset = 1;
	}
	if (key == ESC_KEY)
		exit_mlx(env);
}

void	keyboard_hook(int key, t_env *env)
{
	if (key == M_KEY)
		change_screen_mode(env);
	if (mvt_keys(key) && env->screen_mode == CAMERA_MODE)
		keyboard_move_camera(key, env);
	if (mvt_keys(key) && env->screen_mode == EDIT_MODE && \
			env->selected_obj != NO_OBJ)
		keyboard_move_object(key, env);
	if (key == R_KEY && env->screen_mode == CAMERA_MODE)
	{
		restore_origin_cam(env);
		env->win.need_reset = 1;
	}
	if (key == P_KEY)
		make_screen_shoot(env);
	if (key == L_KEY)
		env->screen_mode = LIGHT_OBJ;
	if (env->screen_mode == LIGHT_OBJ)
		manage_light_pos(key, env);
	if (key == 99)
	{
		env->win.need_reset = 1;
		env->litle_resolution = !env->litle_resolution;
	}
	keyboard_hook_part2(key, env);
}
