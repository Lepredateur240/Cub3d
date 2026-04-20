/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:13:20 by masenche          #+#    #+#             */
/*   Updated: 2026/04/20 10:06:54 by algasnie         ###   ########.fr       */
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
		ft_perror("Failed to initialize MLX");
		exit(1);
	}
	load_textures(game);
	game->mlx.window = mlx_new_window(game->mlx.mlx, info);
	if (!game->mlx.window)
	{
		ft_perror("Failed to create window");
		exit(1);
	}
	mlx_mouse_hide(game->mlx.mlx);
	game->mlx.image = mlx_new_image(game->mlx.mlx, info->width, info->height);
	if (!game->mlx.image)
	{
		ft_perror("Failed to create image");
		exit(1);
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
