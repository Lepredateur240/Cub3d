/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:36:44 by masenche          #+#    #+#             */
/*   Updated: 2026/04/03 20:00:28 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(int keycode, void *param)
{
	t_game	*game;

	printf("Key pressed: %d\n", keycode);
	game = (t_game *)param;
	if (keycode == KEY_ESC || keycode == KEY_ESC)
		cleanup_and_exit(game);
	move_player(game, keycode);
}

void    move_player(t_game *game, int keycode)
{
    double moveSpeed;
    double rotSpeed;
    double oldDirX;
    double oldPlaneX;

	moveSpeed = 0.1;
	rotSpeed = 0.05;
    // --- AVANCER (W ou Z) ---
    if (keycode == KEY_W)
    {
        if (game->data.map[(int)game->data.posY][(int)(game->data.posX + game->data.dirX * moveSpeed)] == 0)
            game->data.posX += game->data.dirX * moveSpeed;
        if (game->data.map[(int)(game->data.posY + game->data.dirY * moveSpeed)][(int)game->data.posX] == 0)
            game->data.posY += game->data.dirY * moveSpeed;
    }
    // --- RECULER (S) ---
    if (keycode == KEY_S)
    {
        if (game->data.map[(int)game->data.posY][(int)(game->data.posX - game->data.dirX * moveSpeed)] == 0)
            game->data.posX -= game->data.dirX * moveSpeed;
        if (game->data.map[(int)(game->data.posY - game->data.dirY * moveSpeed)][(int)game->data.posX] == 0)
            game->data.posY -= game->data.dirY * moveSpeed;
    }
    // --- ROTATION DROITE (D) ---
    if (keycode == KEY_D)
    {
        oldDirX = game->data.dirX;
        game->data.dirX = game->data.dirX * cos(-rotSpeed) - game->data.dirY * sin(-rotSpeed);
        game->data.dirY = oldDirX * sin(-rotSpeed) + game->data.dirY * cos(-rotSpeed);
        oldPlaneX = game->data.planeX;
        game->data.planeX = game->data.planeX * cos(-rotSpeed) - game->data.planeY * sin(-rotSpeed);
        game->data.planeY = oldPlaneX * sin(-rotSpeed) + game->data.planeY * cos(-rotSpeed);
    }
    // --- ROTATION GAUCHE (A ou Q) ---
    if (keycode == KEY_A)
    {
        oldDirX = game->data.dirX;
        game->data.dirX = game->data.dirX * cos(rotSpeed) - game->data.dirY * sin(rotSpeed);
        game->data.dirY = oldDirX * sin(rotSpeed) + game->data.dirY * cos(rotSpeed);
        oldPlaneX = game->data.planeX;
        game->data.planeX = game->data.planeX * cos(rotSpeed) - game->data.planeY * sin(rotSpeed);
        game->data.planeY = oldPlaneX * sin(rotSpeed) + game->data.planeY * cos(rotSpeed);
    }
}
