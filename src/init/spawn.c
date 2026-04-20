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
		game->data.dir_x = 1.0;
		game->data.dir_y = 0.0;
		game->data.plane_x = 0.0;
		game->data.plane_y = 0.66;
	}
	else if (o == 'W')
	{
		game->data.dir_x = -1.0;
		game->data.dir_y = 0.0;
		game->data.plane_x = 0.0;
		game->data.plane_y = -0.66;
	}
}

void	spawn_player(t_game *game, double x, double y, char o)
{
	game->data.pos_x = x + 0.5;
	game->data.pos_y = y + 0.5;
	if (o == 'N')
	{
		game->data.dir_x = 0.0;
		game->data.dir_y = -1.0;
		game->data.plane_x = 0.66;
		game->data.plane_y = 0.0;
	}
	else if (o == 'S')
	{
		game->data.dir_x = 0.0;
		game->data.dir_y = 1.0;
		game->data.plane_x = -0.66;
		game->data.plane_y = 0.0;
	}
	spawn_player2(game, o);
}
