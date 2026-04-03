/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:36:44 by masenche          #+#    #+#             */
/*   Updated: 2026/04/03 21:11:32 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook(int keycode, void *param)
{
	t_game	*game;

	//printf("Key pressed: %d\n", keycode);
	game = (t_game *)param;
	if (keycode == KEY_ESC)
		cleanup_and_exit(game);
	move_player(game, keycode);
	//render_frame((t_game *)game);
}

void    move_player(t_game *game, int keycode)
{
    double moveSpeed = 0.5;
    double rotSpeed = 0.02;
    double oldDirX;
    double oldPlaneX;

	printf("BEFORE: posX=%.2f posY=%.2f\n", game->data.posX, game->data.posY);
    // --- AVANCER (W) ---
    if (keycode == KEY_W) // Ou KEY_W
    {
        if (worldMap[(int)game->data.posY][(int)(game->data.posX + game->data.dirX * moveSpeed)] == 0)
            game->data.posX += game->data.dirX * moveSpeed;
        if (worldMap[(int)(game->data.posY + game->data.dirY * moveSpeed)][(int)game->data.posX] == 0)
            game->data.posY += game->data.dirY * moveSpeed;
    }
    // --- RECULER (S) ---
    if (keycode == KEY_S)
    {
        // 2. On remplace game->data.map par worldMap
        if (worldMap[(int)game->data.posY][(int)(game->data.posX - game->data.dirX * moveSpeed)] == 0)
            game->data.posX -= game->data.dirX * moveSpeed;
        if (worldMap[(int)(game->data.posY - game->data.dirY * moveSpeed)][(int)game->data.posX] == 0)
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
    
    // --- ROTATION GAUCHE (A) ---
    if (keycode == KEY_A)
    {
        oldDirX = game->data.dirX;
        game->data.dirX = game->data.dirX * cos(rotSpeed) - game->data.dirY * sin(rotSpeed);
        game->data.dirY = oldDirX * sin(rotSpeed) + game->data.dirY * cos(rotSpeed);
        oldPlaneX = game->data.planeX;
        game->data.planeX = game->data.planeX * cos(rotSpeed) - game->data.planeY * sin(rotSpeed);
        game->data.planeY = oldPlaneX * sin(rotSpeed) + game->data.planeY * cos(rotSpeed);
    }
	printf("AFTER:  posX=%.2f posY=%.2f\n", game->data.posX, game->data.posY);
}
