/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 19:30:21 by masenche          #+#    #+#             */
/*   Updated: 2026/04/18 13:42:24 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	calculate_texture_x(t_ray *ray, t_draw *draw)
{
	draw->wall_x -= floor(draw->wall_x);
	draw->tex_x = (int)(draw->wall_x * (double)draw->tex_width);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		draw->tex_x = draw->tex_width - draw->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		draw->tex_x = draw->tex_width - draw->tex_x - 1;
}

static void	texture_mapping(t_game *game, t_ray *ray,
	t_perp *perp, t_draw *draw)
{
	draw->tex_width = 1024;
	draw->tex_height = 1024;
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			draw->current_tex = game->data.tex_west;
		else
			draw->current_tex = game->data.tex_east;
	}
	else
	{
		if (ray->ray_dir_y > 0)
			draw->current_tex = game->data.tex_north;
		else
			draw->current_tex = game->data.tex_south;
	}
	if (ray->side == 0)
		draw->wall_x = game->data.pos_y + perp->perp_wall_dist * ray->ray_dir_y;
	else
		draw->wall_x = game->data.pos_x + perp->perp_wall_dist * ray->ray_dir_x;
	calculate_texture_x(ray, draw);
}

static void	draw_wall_ceiling(t_game *game, t_perp *perp, int x, t_draw *draw)
{
	draw->y = 0;
	while (draw->y < perp->draw_start)
	{
		mlx_set_image_pixel(game->mlx.mlx, game->mlx.image,
			x, draw->y, game->data.color_ceiling);
		draw->y++;
	}
	draw->step = 1.0 * draw->tex_height / perp->line_height;
	draw->tex_pos = (perp->draw_start - game->view.height / 2.0
			+ perp->line_height / 2.0) * draw->step;
	draw->y = perp->draw_start;
	while (draw->y < perp->draw_end)
	{
		draw->tex_y = (int)draw->tex_pos;
		if (draw->tex_y >= draw->tex_height)
			draw->tex_y = draw->tex_height - 1;
		else if (draw->tex_y < 0)
			draw->tex_y = 0;
		draw->tex_pos += draw->step;
		draw->color = mlx_get_image_pixel(game->mlx.mlx,
				draw->current_tex, draw->tex_x, draw->tex_y);
		mlx_set_image_pixel(game->mlx.mlx, game->mlx.image,
			x, draw->y, draw->color);
		draw->y++;
	}
}

void	draw_textured_line(t_game *game, t_ray *ray, t_perp *perp, int x)
{
	t_draw	draw;

	texture_mapping(game, ray, perp, &draw);
	draw_wall_ceiling(game, perp, x, &draw);
	draw.y = perp->draw_end;
	while (draw.y < game->view.height)
	{
		mlx_set_image_pixel(game->mlx.mlx, game->mlx.image,
			x, draw.y, game->data.color_floor);
		draw.y++;
	}
}
