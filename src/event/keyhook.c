/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:36:44 by masenche          #+#    #+#             */
/*   Updated: 2026/04/20 10:22:17 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hook_down(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		cleanup_and_exit(game);
	if (keycode >= 0 && keycode < 1024)
		game->data.keys[keycode] = 1;
}

void	key_hook_up(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode >= 0 && keycode < 1024)
		game->data.keys[keycode] = 0;
}

void	rotate_player(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cosa;
	double	sina;

	cosa = cos(angle);
	sina = sin(angle);
	old_dir_x = game->data.dir_x;
	game->data.dir_x = game->data.dir_x * cosa - game->data.dir_y * sina;
	game->data.dir_y = old_dir_x * sina + game->data.dir_y * cosa;
	old_plane_x = game->data.plane_x;
	game->data.plane_x = game->data.plane_x * cosa - game->data.plane_y * sina;
	game->data.plane_y = old_plane_x * sina + game->data.plane_y * cosa;
}

static void	move_player(t_game *game, double dir_x, double dir_y)
{
	double	secur_x;
	double	secur_y;

	secur_x = 0;
	secur_y = 0;
	if (dir_x > 0)
		secur_x = HITBOX;
	else if (dir_x < 0)
		secur_x = -HITBOX;
	if (dir_y > 0)
		secur_y = HITBOX;
	else if (dir_y < 0)
		secur_y = -HITBOX;
	if (game->data.map[(int)game->data.pos_y]
		[(int)(game->data.pos_x + dir_x + secur_x)] == 0)
		game->data.pos_x += dir_x;
	if (game->data.map[(int)(game->data.pos_y + dir_y + secur_y)]
		[(int)game->data.pos_x] == 0)
		game->data.pos_y += dir_y;
}

void	update_player(t_game *game)
{
	double	move_speed;

	move_speed = SPEED;
	if ((game->data.keys[KEY_W]
			&& (game->data.keys[KEY_D] || game->data.keys[KEY_A]))
		|| (game->data.keys[KEY_S]
			&& (game->data.keys[KEY_D] || game->data.keys[KEY_A])))
		move_speed = SPEED / 1.41;
	if (game->data.keys[KEY_W])
		move_player(game, game->data.dir_x * move_speed,
			game->data.dir_y * move_speed);
	if (game->data.keys[KEY_S])
		move_player(game, game->data.dir_x * -move_speed,
			game->data.dir_y * -move_speed);
	if (game->data.keys[KEY_D])
		move_player(game, game->data.dir_y * -move_speed,
			game->data.dir_x * move_speed);
	if (game->data.keys[KEY_A])
		move_player(game, game->data.dir_y * move_speed,
			game->data.dir_x * -move_speed);
	if (game->data.keys[KEY_RIGHT])
		rotate_player(game, SPEED);
	if (game->data.keys[KEY_LEFT])
		rotate_player(game, -SPEED);
	handle_mouse(game);
}
