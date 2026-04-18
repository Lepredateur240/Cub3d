/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:36:44 by masenche          #+#    #+#             */
/*   Updated: 2026/04/18 12:53:11 by algasnie         ###   ########.fr       */
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

static void	rotate_player(t_game *game, double angle)
{
	double	oldDirX;
	double	oldPlaneX;
	double	cosa;
	double	sina;

	cosa = cos(angle);
	sina = sin(angle);

	oldDirX = game->data.dirX;
	game->data.dirX = game->data.dirX * cosa - game->data.dirY * sina;
	game->data.dirY = oldDirX * sina + game->data.dirY * cosa;
	oldPlaneX = game->data.planeX;
	game->data.planeX = game->data.planeX * cosa - game->data.planeY * sina;
	game->data.planeY = oldPlaneX * sina + game->data.planeY * cosa;
}

static void move_player(t_game *game, double dir_x, double dir_y)
{
	double	secur_x;
	double	secur_y;

	secur_x = 0;
	secur_y = 0;
	if (dir_x > 0)
		secur_x = hitBox;
	else if (dir_x < 0)
		secur_x = -hitBox;
	if (dir_y > 0)
		secur_y = hitBox;
	else if (dir_y < 0)
		secur_y = -hitBox;
	if (game->data.map[(int)game->data.posY][(int)(game->data.posX + dir_x + secur_x)] == 0)
		game->data.posX += dir_x;
	if (game->data.map[(int)(game->data.posY + dir_y + secur_y)][(int)game->data.posX] == 0)
		game->data.posY += dir_y;
}

static void	handle_mouse(t_game *game)
{
	int	x;
	int	y;
	int	margin;

	margin = 1;

	if (game->data.mouse_pos[0] == 0 && game->data.mouse_pos[1] == 0)
		mlx_mouse_move(game->mlx.mlx, game->mlx.window, game->view.width / 2, game->view.height / 2);

	mlx_mouse_get_pos(game->mlx.mlx, &x, &y);
	
	if ((x - game->data.mouse_pos[0]) != 0)
		rotate_player(game, (x - game->data.mouse_pos[0]) * mouse_sen);

	game->data.mouse_pos[0] = x;
	game->data.mouse_pos[1] = y;
	
	if (x <= margin || x >= game->view.width - margin || y <= margin || y >= game->view.height - margin)
	{
		mlx_mouse_move(game->mlx.mlx, game->mlx.window, game->view.width / 2, game->view.height / 2);
		game->data.mouse_pos[0] = game->view.width / 2;
		game->data.mouse_pos[1] = game->view.height / 2;
	}

}

void	update_player(t_game *game)
{
	double moveSpeed;
	
	moveSpeed = speed;
	if ((game->data.keys[KEY_W] && (game->data.keys[KEY_D] || game->data.keys[KEY_A]))
		|| (game->data.keys[KEY_S] && (game->data.keys[KEY_D] || game->data.keys[KEY_A])))
		moveSpeed = speed / 1.41;
	if (game->data.keys[KEY_W])
		move_player(game, game->data.dirX * moveSpeed, game->data.dirY * moveSpeed);
	if (game->data.keys[KEY_S])
		move_player(game, game->data.dirX * -moveSpeed, game->data.dirY * -moveSpeed);
	if (game->data.keys[KEY_D])
		move_player(game, game->data.dirY * -moveSpeed, game->data.dirX * moveSpeed);
	if (game->data.keys[KEY_A])
		move_player(game, game->data.dirY * moveSpeed, game->data.dirX * -moveSpeed);
	if (game->data.keys[KEY_RIGHT])
		rotate_player(game, speed);
	if (game->data.keys[KEY_LEFT])
		rotate_player(game, -speed);

	handle_mouse(game);
		

}


