/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:25:37 by masenche          #+#    #+#             */
/*   Updated: 2026/04/16 17:20:17 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_game *game)
{
	int	width;
	int	height;

	if (game->data.path_text_north)
		game->data.tex_north = mlx_new_image_from_file(game->mlx.mlx, game->data.path_text_north, &width, &height);
	if (game->data.path_text_south)
		game->data.tex_south = mlx_new_image_from_file(game->mlx.mlx, game->data.path_text_south, &width, &height);
	if (game->data.path_text_east)
		game->data.tex_east = mlx_new_image_from_file(game->mlx.mlx, game->data.path_text_east, &width, &height);
	if (game->data.path_text_west)
		game->data.tex_west = mlx_new_image_from_file(game->mlx.mlx, game->data.path_text_west, &width, &height);
	if (!game->data.tex_north || !game->data.tex_south || !game->data.tex_east || !game->data.tex_west)
		ft_perror("Erreur : Impossible de charger les textures JPG");

}
