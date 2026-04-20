/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 17:32:05 by masenche          #+#    #+#             */
/*   Updated: 2026/04/20 11:05:40 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dda_step(t_ray *ray, t_game *game)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->data.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->data.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->data.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->data.pos_y)
			* ray->delta_dist_y;
	}
}

static void	dda(t_ray *ray, t_game *game)
{
	ray->map_x = (int)game->data.pos_x;
	ray->map_y = (int)game->data.pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	ray->hit = 0;
	dda_step(ray, game);
}

static void	launch_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->data.map[ray->map_y][ray->map_x] > 0)
			ray->hit = 1;
	}
}

static void	perp_wall_dist(t_ray *ray, t_game *game, t_perp *perp)
{
	if (ray->side == 0)
		perp->perp_wall_dist = (ray->map_x - game->data.pos_x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		perp->perp_wall_dist = (ray->map_y - game->data.pos_y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y;
	perp->line_height = (int)(game->view.height / perp->perp_wall_dist);
	perp->draw_start = -perp->line_height / 2 + game->view.height / 2;
	if (perp->draw_start < 0)
		perp->draw_start = 0;
	perp->draw_end = perp->line_height / 2 + game->view.height / 2;
	if (perp->draw_end >= game->view.height)
		perp->draw_end = game->view.height - 1;
}

void	to_3d(t_game *game)
{
	int			x;
	t_ray		ray;
	t_perp		perp;
	mlx_color	black;

	black.rgba = 0x000000FF;
	mlx_clear_window(game->mlx.mlx, game->mlx.window, black);
	x = 0;
	while (x < game->view.width)
	{
		ray.camera_x = 2 * x / (double)game->view.width - 1;
		ray.ray_dir_x = game->data.dir_x + game->data.plane_x * ray.camera_x;
		ray.ray_dir_y = game->data.dir_y + game->data.plane_y * ray.camera_x;
		dda(&ray, game);
		launch_dda(game, &ray);
		perp_wall_dist(&ray, game, &perp);
		draw_textured_line(game, &ray, &perp, x);
		x++;
	}
}
