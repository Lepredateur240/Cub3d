/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:07:12 by masenche          #+#    #+#             */
/*   Updated: 2026/04/03 18:43:03 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_frame(void *param)
{
    t_game *game = (t_game *)param;

    // 1. On lance le calcul du Raycasting
    to_3d(game);

    // 2. On affiche l'image sur la fenêtre
    // (L'ordre des paramètres dépend de ta version de MacroLibX)
    mlx_put_image_to_window(game->mlx.mlx, game->mlx.window, game->mlx.image, 0, 0);
}

int main(void)
{
	t_game	game;

	init_mlx(&game);
	mlx_loop(game.mlx.mlx);
	return 0;
}