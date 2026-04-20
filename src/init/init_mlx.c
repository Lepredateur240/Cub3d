/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:13:20 by masenche          #+#    #+#             */
/*   Updated: 2026/04/20 14:29:18 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_data_view(t_game *game, mlx_window_create_info *info)
{
	info->width = 1280;
	info->height = 1024;
	info->title = "Cub3D";
	info->is_fullscreen = false;
	info->is_resizable = true;
	game->view.width = info->width;
	game->view.height = info->height;
}

static void	init_app(t_game *game, mlx_window_create_info *info)
{
	game->mlx.mlx = mlx_init();
	if (!game->mlx.mlx)
	{
		write(2, "Error\nFailed to initialize MLX\n", 32);
		cleanup_and_exit(game);
	}
	load_textures(game);
	game->mlx.window = mlx_new_window(game->mlx.mlx, info);
	if (!game->mlx.window)
	{
		write(2, "Error\nFailed to init mlx window\n", 33);
		cleanup_and_exit(game);
	}
	mlx_mouse_hide(game->mlx.mlx);
	game->mlx.image = mlx_new_image(game->mlx.mlx, info->width, info->height);
	if (!game->mlx.image)
	{
		write(2, "Error\nFailed to init mlx image\n", 32);
		cleanup_and_exit(game);
	}
}

void	init_mlx(char **argv, t_game *game)
{
	mlx_window_create_info	info;

	ft_memset(game, 0, sizeof(t_game));
	ft_memset(&info, 0, sizeof(mlx_window_create_info));
	if (init_map(argv, game))
		exit (1);
	init_data_view(game, &info);
	init_app(game, &info);
	run_game_loop(game);
}
