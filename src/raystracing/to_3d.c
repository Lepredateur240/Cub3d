/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:32:05 by masenche          #+#    #+#             */
/*   Updated: 2026/04/03 20:03:19 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

extern int worldMap[24][24];

static void	dda_step(t_ray *ray, t_game *game)
{
	printf("Calculating DDA step for ray at cameraX: %f\n", ray->cameraX);
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
	printf("DDA step calculated: stepX: %d, stepY: %d, sideDistX: %f, sideDistY: %f\n",
		ray->stepX, ray->stepY, ray->sideDistX, ray->sideDistY);
}

static void	dda(t_ray *ray, t_game *game)
{
	printf("Setting up DDA for ray at cameraX: %f\n", ray->cameraX);
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
	printf("Initial DDA setup: mapX: %d, mapY: %d, rayDirX: %f, rayDirY: %f, deltaDistX: %f, deltaDistY: %f\n",
		ray->mapX, ray->mapY, ray->rayDirX, ray->rayDirY, ray->deltaDistX, ray->deltaDistY);
	dda_step(ray, game);
}

static void	launch_dda(t_ray *ray)
{
	printf("Launching DDA for ray at mapX: %d, mapY: %d\n", ray->mapX, ray->mapY);
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
		if (worldMap[ray->mapY][ray->mapX] > 0)
			ray->hit = 1;
	}
	printf("DDA hit wall at mapX: %d, mapY: %d, side: %d\n", ray->mapX, ray->mapY, ray->side);
}

static void	PerpWallDist(t_ray *ray, t_game *game, t_perp *perp)
{
	printf("Calculating perpendicular wall distance for ray at mapX: %d, mapY: %d\n", ray->mapX, ray->mapY);
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
	printf("Perpendicular wall distance: %f, lineHeight: %d, drawStart: %d, drawEnd: %d\n",
		perp->perpWallDist, perp->lineHeight, perp->drawStart, perp->drawEnd);
}

void	to_3d(t_game *game)
{
	int x;

	x = 0;
	printf("Starting 3D rendering loop for view width: %d\n", game->view.width);
	while (x < game->view.width)
	{
		//calculate ray position and direction
		t_ray ray;
		t_perp perp;

		ray.cameraX = 2 * x / (double)game->view.width - 1; //x-coordinate in camera space
		ray.rayDirX = game->data.dirX + game->data.planeX * ray.cameraX;
		ray.rayDirY = game->data.dirY + game->data.planeY * ray.cameraX;
		//which box of the map we're in
		printf("Calculating ray for column %d: cameraX: %f, rayDirX: %f, rayDirY: %f\n",
			x, ray.cameraX, ray.rayDirX, ray.rayDirY);
		dda(&ray, game);
		launch_dda(&ray);
		PerpWallDist(&ray, game, &perp);
		init_image(game, &ray, &perp, x);
		x++;
		printf("Finished rendering column %d\n", x);
	}
	printf("Finished 3D rendering loop\n");
}
