/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jodde <jodde@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:04:51 by nlaporte          #+#    #+#             */
/*   Updated: 2026/02/04 19:38:08 by jodde            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "../lib/mlx/mlx.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_env	env;

	if (ac != 2)
		return (printf("Error: need scene un param\n"), 0);
	if (init_env(&env, av[1]))
		return (printf("Error: bad file\n"), 0);
	if (init_win(&env, WIDTH, HEIGHT))
		return ((exit_mlx(&env), 0));
	if (prepare_parsing(&env, env.file))
		return ((exit_mlx(&env), 0));
	if (init_tasks(&env))
		return ((exit_mlx(&env), 0));
	env.win.count = 1;
	env.litle_resolution = 1;
	mlx_hook(env.win.win, 2, 1L << 0, (void *)&keyboard_hook, &env);
	mlx_hook(env.win.win, 3, 1L << 0, (void *)&keyboard_release, &env);
	mlx_mouse_hook(env.win.win, (void *)&mouse_hook, &env);
	mlx_hook(env.win.win, 5, 1L << 3, (void *)&mouse_release, &env);
	mlx_hook(env.win.win, 6, 1L << 6, (void *)&mouse_move, &env);
	mlx_hook(env.win.win, 17, 0L, (void *)exit_mlx, &env);
	mlx_loop_hook(env.mlx, (void *)&render, &env);
	mlx_loop(env.mlx);
	exit_mlx(&env);
	return (0);
}
