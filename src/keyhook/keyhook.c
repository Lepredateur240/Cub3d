/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:36:44 by masenche          #+#    #+#             */
/*   Updated: 2026/04/04 13:16:19 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook_down(int keycode, void *param)
{
	t_game	*game = (t_game *)param;

	printf("Key down: %d\n", keycode);
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

void	update_player(t_game *game)
{
    double moveSpeed = 0.05;
    double rotSpeed = 0.03;
    double oldDirX;
    double oldPlaneX;

    // --- AVANCER (W) ---
    if (game->data.keys[KEY_W]) // Ou KEY_W
    {
        if (worldMap[(int)game->data.posY][(int)(game->data.posX + game->data.dirX * moveSpeed)] == 0)
            game->data.posX += game->data.dirX * moveSpeed;
        if (worldMap[(int)(game->data.posY + game->data.dirY * moveSpeed)][(int)game->data.posX] == 0)
            game->data.posY += game->data.dirY * moveSpeed;
    }
    // --- RECULER (S) ---
    if (game->data.keys[KEY_S])
    {
        // 2. On remplace game->data.map par worldMap
        if (worldMap[(int)game->data.posY][(int)(game->data.posX - game->data.dirX * moveSpeed)] == 0)
            game->data.posX -= game->data.dirX * moveSpeed;
        if (worldMap[(int)(game->data.posY - game->data.dirY * moveSpeed)][(int)game->data.posX] == 0)
            game->data.posY -= game->data.dirY * moveSpeed;
    }
    
    // --- ROTATION DROITE (D) ---
    if (game->data.keys[KEY_D] || game->data.keys[KEY_RIGHT])
    {
        oldDirX = game->data.dirX;
        game->data.dirX = game->data.dirX * cos(-rotSpeed) - game->data.dirY * sin(-rotSpeed);
        game->data.dirY = oldDirX * sin(-rotSpeed) + game->data.dirY * cos(-rotSpeed);
        oldPlaneX = game->data.planeX;
        game->data.planeX = game->data.planeX * cos(-rotSpeed) - game->data.planeY * sin(-rotSpeed);
        game->data.planeY = oldPlaneX * sin(-rotSpeed) + game->data.planeY * cos(-rotSpeed);
    }
    
    // --- ROTATION GAUCHE (A) ---
    if (game->data.keys[KEY_A] || game->data.keys[KEY_LEFT])
    {
        oldDirX = game->data.dirX;
        game->data.dirX = game->data.dirX * cos(rotSpeed) - game->data.dirY * sin(rotSpeed);
        game->data.dirY = oldDirX * sin(rotSpeed) + game->data.dirY * cos(rotSpeed);
        oldPlaneX = game->data.planeX;
        game->data.planeX = game->data.planeX * cos(rotSpeed) - game->data.planeY * sin(rotSpeed);
        game->data.planeY = oldPlaneX * sin(rotSpeed) + game->data.planeY * cos(rotSpeed);
    }
}
