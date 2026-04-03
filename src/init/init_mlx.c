/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:13:20 by masenche          #+#    #+#             */
/*   Updated: 2026/04/03 20:59:23 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int worldMap[24][24];

static void	init_data_view(t_game *game, mlx_window_create_info *info)
{
	game->data.posX = 22;
	game->data.posY = 12;
	game->data.dirX = -1;
	game->data.dirY = 0;
	game->data.planeX = 0;
	game->data.planeY = 0.66;
	game->data.time = 0;
	game->data.oldTime = 0;
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
		ft_perror("Failed to initialize MLX");
	game->mlx.window = mlx_new_window(game->mlx.mlx, info);
	if (!game->mlx.window)
		ft_perror("Failed to create window");
	game->mlx.image = mlx_new_image(game->mlx.mlx, info->width, info->height);
	if (!game->mlx.image)
		ft_perror("Failed to create image");
}

void	init_mlx(t_game *game)
{
	mlx_window_create_info info;

	ft_memset(game, 0, sizeof(t_game));
	ft_memset(&info, 0, sizeof(mlx_window_create_info));
	init_data_view(game, &info);
	init_app(game, &info);
	run_game_loop(game);
}