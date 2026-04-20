/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:36:44 by masenche          #+#    #+#             */
/*   Updated: 2026/04/20 11:04:33 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_mouse(t_game *game)
{
	int	x;
	int	y;
	int	center_x;
	int	center_y;

	if (BONUS == 0)
		return ;
	center_x = game->view.width / 2;
	center_y = game->view.height / 2;
	mlx_mouse_get_pos(game->mlx.mlx, &x, &y);
	if (x != center_x)
	{
		rotate_player(game, (x - center_x) * MOUSE_SEN);
		mlx_mouse_move(game->mlx.mlx, game->mlx.window, center_x, center_y);
	}
}
