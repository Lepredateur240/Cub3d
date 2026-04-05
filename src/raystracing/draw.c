/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 19:30:21 by masenche          #+#    #+#             */
/*   Updated: 2026/04/05 20:39:28 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void calculate_texture_x(t_ray *ray, t_draw *draw)
{
	draw->wallX -= floor(draw->wallX);
	draw->texX = (int)(draw->wallX * (double)draw->texWidth);
	if (ray->side == 0 && ray->rayDirX > 0)
		draw->texX = draw->texWidth - draw->texX - 1;
	if (ray->side == 1 && ray->rayDirY < 0)
		draw->texX = draw->texWidth - draw->texX - 1;
}

static void	texture_mapping(t_game *game, t_ray *ray, t_perp *perp, t_draw *draw)
{
	draw->texWidth = 1024;
	draw->texHeight = 1024;
	if (ray->side == 0)
	{
		if (ray->rayDirX > 0)
			draw->current_tex = game->data.tex_west;
		else
			draw->current_tex = game->data.tex_east;
	}
	else
	{
		if (ray->rayDirY > 0)
			draw->current_tex = game->data.tex_south;
		else
			draw->current_tex = game->data.tex_north;
	}
	if (ray->side == 0)
		draw->wallX = game->data.posY + perp->perpWallDist * ray->rayDirY;
	else
		draw->wallX = game->data.posX + perp->perpWallDist * ray->rayDirX;
	calculate_texture_x(ray, draw);

}

static void	draw_wall_ceiling(t_game *game, t_perp *perp, int x, t_draw *draw)
{
	// --- PLAFOND ---
	draw->y = 0;
	while (draw->y < perp->drawStart)
	{
		// Couleur Bleu Ciel
		mlx_set_image_pixel(game->mlx.mlx, game->mlx.image, x, draw->y, COLOR_CEILING);
		draw->y++;
	}
	// --- MUR TEXTURÉ ---
	draw->step = 1.0 * draw->texHeight / perp->lineHeight;
	draw->texPos = (perp->drawStart - game->view.height / 2.0 + perp->lineHeight / 2.0) * draw->step;
	draw->y = perp->drawStart;
	while (draw->y < perp->drawEnd)
	{
		draw->texY = (int)draw->texPos;
		if (draw->texY >= draw->texHeight)
			draw->texY = draw->texHeight - 1;
		else if (draw->texY < 0)
			draw->texY = 0;
		draw->texPos += draw->step;
		draw->color = mlx_get_image_pixel(game->mlx.mlx, draw->current_tex, draw->texX, draw->texY);
		mlx_set_image_pixel(game->mlx.mlx, game->mlx.image, x, draw->y, draw->color);
		draw->y++;
	}
}

void	draw_textured_line(t_game *game, t_ray *ray, t_perp *perp, int x)
{
	t_draw draw;

	texture_mapping(game, ray, perp, &draw);
	draw.texX = (int)(draw.wallX * (double)draw.texWidth);
	// Inversion de la texture pour certaines faces
	if (ray->side == 0 && ray->rayDirX > 0)
		draw.texX = draw.texWidth - draw.texX - 1;
	if (ray->side == 1 && ray->rayDirY < 0)
		draw.texX = draw.texWidth - draw.texX - 1;
	draw_wall_ceiling(game, perp, x, &draw);
	draw.y = perp->drawEnd;
	while (draw.y < game->view.height)
	{
		mlx_set_image_pixel(game->mlx.mlx, game->mlx.image, x, draw.y, COLOR_FLOOR);
		draw.y++;
	}
}
