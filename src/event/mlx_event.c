/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:48:10 by masenche          #+#    #+#             */
/*   Updated: 2026/04/20 14:18:07 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_and_exit(t_game *game)
{
	if (game->data.tex_north)
		mlx_destroy_image(game->mlx.mlx, game->data.tex_north);
	if (game->data.tex_south)
		mlx_destroy_image(game->mlx.mlx, game->data.tex_south);
	if (game->data.tex_east)
		mlx_destroy_image(game->mlx.mlx, game->data.tex_east);
	if (game->data.tex_west)
		mlx_destroy_image(game->mlx.mlx, game->data.tex_west);
	if (game->mlx.mlx && game->mlx.image)
		mlx_destroy_image(game->mlx.mlx, game->mlx.image);
	ft_free_init(game, NULL);
	if (game->mlx.mlx && game->mlx.window)
		mlx_destroy_window(game->mlx.mlx, game->mlx.window);
	if (game->mlx.mlx)
		mlx_destroy_context(game->mlx.mlx);
	exit(0);
}

static void	window_hook(int event, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (event == 0)
		cleanup_and_exit(game);
}

void	run_game_loop(t_game *game)
{
	mlx_on_event(game->mlx.mlx, game->mlx.window,
		MLX_KEYDOWN, key_hook_down, game);
	mlx_on_event(game->mlx.mlx, game->mlx.window,
		MLX_KEYUP, key_hook_up, game);
	mlx_on_event(game->mlx.mlx, game->mlx.window,
		MLX_WINDOW_EVENT, window_hook, game);
	mlx_add_loop_hook(game->mlx.mlx, render_loop, game);
	mlx_loop(game->mlx.mlx);
}
