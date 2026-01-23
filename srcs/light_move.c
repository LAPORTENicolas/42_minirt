/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:08:21 by nlaporte          #+#    #+#             */
/*   Updated: 2026/01/21 16:24:31 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdio.h>

void	manage_light_pos(int key, t_env *env)
{
	if (!env->light_to_move)
		env->light_to_move = env->scene.lights;
	else if (key == N_KEY)
	{
		if (env->light_to_move->next)
			env->light_to_move = env->light_to_move->next;
		else
			env->light_to_move = env->scene.lights;
	}
	else if (key == O_KEY)
	{
		env->light_to_move2->brightness += .1;
		if (env->light_to_move2->brightness >= 1.)
			env->light_to_move2->brightness = 1;
	}
	else if (key == I_KEY)
	{
		env->light_to_move2->brightness -= .1;
		if (env->light_to_move2->brightness <= 0)
			env->light_to_move2->brightness = 0.;
	}
	env->light_to_move2 = env->light_to_move->content;
	env->selected_obj = LIGHT_OBJ;
	keyboard_move_object(key, env);
}
