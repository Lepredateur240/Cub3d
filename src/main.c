/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:07:12 by masenche          #+#    #+#             */
/*   Updated: 2026/04/03 21:14:11 by masenche         ###   ########.fr       */
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

void 	render_loop(void *param)
{
	//printf("RENDER LOOP CALLED\n");
	render_frame((t_game *)param);
}

int main(void)
{
	t_game	game;

	init_mlx(&game);
	return 0;
}