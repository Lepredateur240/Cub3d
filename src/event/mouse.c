/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:36:44 by masenche          #+#    #+#             */
/*   Updated: 2026/04/20 15:21:54 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_mouse(t_game *game)
{
	if (BONUS == 0)
		return ;
	if (game->data.mouse_pos[0] == 0 && game->data.mouse_pos[1] == 0)
		mlx_mouse_move(game->mlx.mlx, game->mlx.window, game->view.width / 2, game->view.height / 2);
	mlx_mouse_get_pos(game->mlx.mlx, &game->data.mouse_pos[0], &game->data.mouse_pos[1]);
	if (game->data.mouse_pos[0] != game->view.width / 2)
	{
		rotate_player(game, (game->data.mouse_pos[0] - (game->view.width / 2)) * MOUSE_SEN);
		mlx_mouse_move(game->mlx.mlx, game->mlx.window, game->view.width / 2, game->view.height / 2);
	}
}
