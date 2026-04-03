/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:48:10 by masenche          #+#    #+#             */
/*   Updated: 2026/04/03 20:03:55 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_and_exit(t_game *game)
{
	printf("Cleaning up resources and exiting...\n");
	mlx_destroy_image(game->mlx.mlx, game->mlx.image);
	mlx_destroy_window(game->mlx.mlx, game->mlx.window);
	mlx_destroy_context(game->mlx.mlx);
	exit(0);
}

void	window_hook(int event, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (event == MLX_WINDOW_EVENT)
		cleanup_and_exit(game);
}

void run_game_loop(t_game *game)
{
	printf("Entering game loop...\n");
    mlx_on_event(game->mlx.mlx, game->mlx.window, MLX_KEYDOWN, key_hook, game);
    mlx_add_loop_hook(game->mlx.mlx, render_frame, game);
	mlx_on_event(game->mlx.mlx, game->mlx.window, MLX_WINDOW_EVENT, window_hook, game);
    mlx_loop(game->mlx.mlx);
}

