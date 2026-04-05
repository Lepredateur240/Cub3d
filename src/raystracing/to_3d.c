/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:32:05 by masenche          #+#    #+#             */
/*   Updated: 2026/04/05 20:36:32 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dda_step(t_ray *ray, t_game *game)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->data.posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - game->data.posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->data.posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - game->data.posY) * ray->deltaDistY;
	}
}

static void	dda(t_ray *ray, t_game *game)
{
	ray->mapX = (int)game->data.posX;
	ray->mapY = (int)game->data.posY;
	if (ray->rayDirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray->hit = 0;
	dda_step(ray, game);
}

static void	launch_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (game->data.map[ray->mapY][ray->mapX] > 0)
			ray->hit = 1;
	}
}

static void	PerpWallDist(t_ray *ray, t_game *game, t_perp *perp)
{
	if (ray->side == 0)
		perp->perpWallDist = (ray->mapX - game->data.posX + (1 - ray->stepX) / 2) / ray->rayDirX;
	else
		perp->perpWallDist = (ray->mapY - game->data.posY + (1 - ray->stepY) / 2) / ray->rayDirY;
	perp->lineHeight = (int)(game->view.height / perp->perpWallDist);
	
	// Calcul des pixels de début et de fin de la ligne
	perp->drawStart = -perp->lineHeight / 2 + game->view.height / 2;
	if (perp->drawStart < 0)
		perp->drawStart = 0;
	perp->drawEnd = perp->lineHeight / 2 + game->view.height / 2;
	if (perp->drawEnd >= game->view.height)
		perp->drawEnd = game->view.height - 1;
}
void	to_3d(t_game *game)
{
	int		x;
	t_ray	ray;
	t_perp	perp;

	mlx_clear_window(game->mlx.mlx, game->mlx.window, COLOR_BLACK);
	x = 0;
	while (x < game->view.width)
	{
		ray.cameraX = 2 * x / (double)game->view.width - 1;
		ray.rayDirX = game->data.dirX + game->data.planeX * ray.cameraX;
		ray.rayDirY = game->data.dirY + game->data.planeY * ray.cameraX;
		
		dda(&ray, game);
		launch_dda(game, &ray);
		PerpWallDist(&ray, game, &perp);
		
		// Appel de la nouvelle fonction d'affichage
		draw_textured_line(game, &ray, &perp, x);
		
		x++;
	}
}
