/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:10:29 by jodde             #+#    #+#             */
/*   Updated: 2026/01/15 17:23:39 by nlaporte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mouse_move(int x, int y, void *param)
{
	t_env	*env;
	int		dy;
	int		dx;

	env = (t_env *)param;
	dx = x - env->mouse_x;
	dy = y - env->mouse_y;
	if (env->mouse_left && env->screen_mode == CAMERA_MODE)
	{
		rotate_camera(&env->camera, dx, dy);
		env->win.need_reset = 1;
	}
	env->mouse_x = x;
	env->mouse_y = y;
	return (0);
}

int	mouse_release(int button, int x, int y, void *param)
{
	t_env	*env;

	(void)x;
	(void)y;
	env = param;
	if (button == 1)
		env->mouse_left = 0;
	if (button == 3)
		env->mouse_right = 0;
	return (0);
}

int	mouse_hook(int button, int x, int y, void *param)
{
	t_env	*env;

	env = (t_env *)param;
	env->mouse_x = x;
	env->mouse_y = y;
	if (env->screen_mode == CAMERA_MODE)
	{
		env->selected_obj = NO_OBJ;
		handle_camera_mouse(button, env);
	}
	if (env->screen_mode == EDIT_MODE)
		handle_edit_mouse(button, env);
	return (0);
}
