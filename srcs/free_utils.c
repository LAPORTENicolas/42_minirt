/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:26:34 by jodde             #+#    #+#             */
/*   Updated: 2026/01/21 20:38:45 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/mlx/mlx.h"
#include "minirt.h"
#include <stdio.h>
#include <stdlib.h>

void	free_backup_obj(t_env *env)
{
	if (env->backup_sphere)
		free(env->backup_sphere);
	if (env->backup_plane)
		free(env->backup_plane);
	if (env->backup_cylinder)
		free(env->backup_cylinder);
	if (env->backup_cone)
		free(env->backup_cone);
}

void	free_lists(t_env *env)
{
	ft_lstclear(&env->scene.spheres, free);
	ft_lstclear(&env->scene.planes, free);
	ft_lstclear(&env->scene.cylinders, free);
	ft_lstclear(&env->scene.cones, free);
	ft_lstclear(&env->scene.lights, free);
	ft_lstclear(&env->scene.textures, free_texture);
}
