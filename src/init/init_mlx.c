/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:13:20 by masenche          #+#    #+#             */
/*   Updated: 2026/04/14 15:36:37 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_spawn(t_game *game, int x, int y)
{
	char c = game->data.map[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		spawn_player(game, x + 0.5, y + 0.5, c);
		game->data.map[y][x] = 0;
	}
}

static void	init_data_view(t_game *game, mlx_window_create_info *info)
{
	int		x;
	int		y;

	x = 0;
	while (x < 24) /// taille de map
	{
		y = 0;
		while (y < 24)
		{
			check_spawn(game, x, y);
			y++;
		}
		x++;
	}
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
	load_textures(game);
	game->mlx.window = mlx_new_window(game->mlx.mlx, info);
	if (!game->mlx.window)
		ft_perror("Failed to create window");
	game->mlx.image = mlx_new_image(game->mlx.mlx, info->width, info->height);
	if (!game->mlx.image)
		ft_perror("Failed to create image");
}

void	init_mlx(char** argv, t_game *game)
{
	mlx_window_create_info info;

	ft_memset(game, 0, sizeof(t_game));
	ft_memset(&info, 0, sizeof(mlx_window_create_info));
	if (init_map(argv, game))
		exit (1);
	init_data_view(game, &info);
	init_app(game, &info);
	run_game_loop(game);
}
