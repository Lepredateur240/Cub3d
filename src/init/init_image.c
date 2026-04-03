/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:25:37 by masenche          #+#    #+#             */
/*   Updated: 2026/04/03 19:59:21 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int worldMap[24][24];

void	init_image(t_game *game, t_ray *ray, t_perp *perp, int x)
{
	int			y;
    mlx_color	color;
	int			wallType;

    // 1. Dessiner le plafond
    y = 0;
    while (y < perp->drawStart)
    {
		mlx_set_image_pixel(game->mlx.mlx, game->mlx.image, x, y, COLOR_CEILING);
        y++;
    }

    // 2. Dessiner le mur
	wallType = worldMap[ray->mapY][ray->mapX];
	if (wallType == 1)
		color = COLOR_RED;
	else if (wallType == 2)
		color = COLOR_GREEN;
	else if (wallType == 3)
		color = COLOR_BLUE;
	else
    	color = COLOR_WHITE; // Blanc
    if (ray->side == 1)
        color.rgba = 0x7F7F7F; // Gris si face Sud/Nord
    while (y < perp->drawEnd)
    {
        mlx_set_image_pixel(game->mlx.mlx, game->mlx.image, x, y, color); // On utilise bien 'color' ici !
        y++;
    }
    // 3. Dessiner le sol
    while (y < game->view.height)
    {
        mlx_set_image_pixel(game->mlx.mlx, game->mlx.image, x, y, COLOR_FLOOR);
        y++;
    }
}
