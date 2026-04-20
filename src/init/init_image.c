/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:25:37 by masenche          #+#    #+#             */
/*   Updated: 2026/04/20 14:40:11 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int open_test(char  *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	else
	{
		close(fd);
		return (1);
	}
}

void	load_textures(t_game *game)
{
	int	width;
	int	height;

	if (game->data.path_text_north && open_test(game->data.path_text_north))
		game->data.tex_north = mlx_new_image_from_file(game->mlx.mlx,
				game->data.path_text_north, &width, &height);
	if (game->data.path_text_south && open_test(game->data.path_text_south))
		game->data.tex_south = mlx_new_image_from_file(game->mlx.mlx,
				game->data.path_text_south, &width, &height);
	if (game->data.path_text_east && open_test(game->data.path_text_east))
		game->data.tex_east = mlx_new_image_from_file(game->mlx.mlx,
				game->data.path_text_east, &width, &height);
	if (game->data.path_text_west && open_test(game->data.path_text_west))
		game->data.tex_west = mlx_new_image_from_file(game->mlx.mlx,
				game->data.path_text_west, &width, &height);
	if (!game->data.tex_north || !game->data.tex_south
		|| !game->data.tex_east || !game->data.tex_west)
		{
			write(2, "Error\nLoading texture failed\n", 29);
			cleanup_and_exit(game);
		}
}
