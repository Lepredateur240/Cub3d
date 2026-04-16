/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:36:44 by masenche          #+#    #+#             */
/*   Updated: 2026/04/16 17:56:23 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook_down(int keycode, void *param)
{
	t_game	*game = (t_game *)param;

	if (keycode == KEY_ESC)
		cleanup_and_exit(game);
	if (keycode >= 0 && keycode < 1024)
		game->data.keys[keycode] = 1;
}

void	key_hook_up(int keycode, void *param)
{
	t_game	*game = (t_game *)param;

	if (keycode >= 0 && keycode < 1024)
		game->data.keys[keycode] = 0;
}

static void	rotate_player(t_game *game, double rotSpeed)
{
	double	oldDirX;
	double	oldPlaneX;

	oldDirX = game->data.dirX;
	oldPlaneX = game->data.planeX;
	if (game->data.keys[KEY_D] || game->data.keys[KEY_RIGHT])
	{
		oldDirX = game->data.dirX;
		game->data.dirX = game->data.dirX * cos(rotSpeed) - game->data.dirY * sin(rotSpeed);
		game->data.dirY = oldDirX * sin(rotSpeed) + game->data.dirY * cos(rotSpeed);
		oldPlaneX = game->data.planeX;
		game->data.planeX = game->data.planeX * cos(rotSpeed) - game->data.planeY * sin(rotSpeed);
		game->data.planeY = oldPlaneX * sin(rotSpeed) + game->data.planeY * cos(rotSpeed);
	}
	if (game->data.keys[KEY_A] || game->data.keys[KEY_LEFT])
	{
		oldDirX = game->data.dirX;
		game->data.dirX = game->data.dirX * cos(-rotSpeed) - game->data.dirY * sin(-rotSpeed);
		game->data.dirY = oldDirX * sin(-rotSpeed) + game->data.dirY * cos(-rotSpeed);
		oldPlaneX = game->data.planeX;
		game->data.planeX = game->data.planeX * cos(-rotSpeed) - game->data.planeY * sin(-rotSpeed);
		game->data.planeY = oldPlaneX * sin(-rotSpeed) + game->data.planeY * cos(-rotSpeed);
	}
}

void	update_player(t_game *game)
{
	double	moveSpeed = 0.05;
	double	rotSpeed = 0.05;

	if (game->data.keys[KEY_W]) // Ou KEY_W
	{
		if (game->data.map[(int)game->data.posY][(int)(game->data.posX + game->data.dirX * moveSpeed)] == 0)
			game->data.posX += game->data.dirX * moveSpeed;
		if (game->data.map[(int)(game->data.posY + game->data.dirY * moveSpeed)][(int)game->data.posX] == 0)
			game->data.posY += game->data.dirY * moveSpeed;
	}
	if (game->data.keys[KEY_S])
	{
		if (game->data.map[(int)game->data.posY][(int)(game->data.posX - game->data.dirX * moveSpeed)] == 0)
			game->data.posX -= game->data.dirX * moveSpeed;
		if (game->data.map[(int)(game->data.posY - game->data.dirY * moveSpeed)][(int)game->data.posX] == 0)
			game->data.posY -= game->data.dirY * moveSpeed;
	}
	rotate_player(game, rotSpeed);
}
