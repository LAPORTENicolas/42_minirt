/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 18:10:29 by jodde             #+#    #+#             */
/*   Updated: 2026/01/19 17:04:13 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_scroll(int button, t_env *env)
{
	if (button == 4)
	{
		resize_object(env, 1);
		env->win.need_reset = 1;
	}
	if (button == 5)
	{
		resize_object(env, -1);
		env->win.need_reset = 1;
	}
}

void	handle_camera_mouse(int button, t_env *env)
{
	if (button == 1)
		env->mouse_left = 1;
	if (button == 4)
	{
		zoom_in(&env->camera);
		env->win.need_reset = 1;
	}
	if (button == 5)
	{
		zoom_out(&env->camera);
		env->win.need_reset = 1;
	}
}

void	handle_edit_mouse(int button, t_env *env)
{
	if (button == 1)
	{
		select_object(env);
		env->win.need_reset = 1;
		env->mouse_left = 1;
	}
	if (button == 3)
	{
		env->mouse_right = 1;
		env->selected_obj = NO_OBJ;
	}
	if (button == 4 || button == 5)
		handle_scroll(button, env);
}
