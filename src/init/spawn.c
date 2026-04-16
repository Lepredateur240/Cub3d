/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 18:17:30 by masenche          #+#    #+#             */
/*   Updated: 2026/04/16 11:36:33 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	spawn_player2(t_game *game, char o)
{
	if (o == 'E')
	{
		game->data.dirX = 1.0;
		game->data.dirY = 0.0;
		game->data.planeX = 0.0;
		game->data.planeY = 0.66;
	}
	else if (o == 'W')
	{
		game->data.dirX = -1.0;
		game->data.dirY = 0.0;
		game->data.planeX = 0.0;
		game->data.planeY = -0.66;
	}
}

void	spawn_player(t_game *game, double x, double y, char o)
{
	game->data.posX = x + 0.5;
	game->data.posY = y + 0.5;
	if (o == 'N')
	{
		game->data.dirX = 0.0;
		game->data.dirY = -1.0;
		game->data.planeX = 0.66;
		game->data.planeY = 0.0;
	}
	else if (o == 'S')
	{
		game->data.dirX = 0.0;
		game->data.dirY = 1.0;
		game->data.planeX = -0.66;
		game->data.planeY = 0.0;
	}
	spawn_player2(game, o);
}
