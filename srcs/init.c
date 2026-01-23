/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 15:28:39 by jodde             #+#    #+#             */
/*   Updated: 2026/01/21 16:20:34 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../lib/libft/libft.h"
#include <stdio.h>

int	init_env(t_env *env, char *str)
{
	ft_memset(env, 0, sizeof(t_env));
	if (!ft_strrchr(str, '.') || ft_strncmp(ft_strrchr(str, '.'), ".rt", 3))
	{
		printf("Error: Bad file scene need .rt %s\n", ft_strchr(str, '.'));
		return (1);
	}
	env->file = ft_strndup(str, ft_strlen(str));
	if (!env->file)
		return (1);
	env->win.need_reset = 1;
	return (0);
}
