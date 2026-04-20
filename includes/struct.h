/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:26:56 by masenche          #+#    #+#             */
/*   Updated: 2026/04/20 10:07:02 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "../mlx/includes/mlx.h"

typedef struct s_data
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			mouse_pos[2];
	int			**map;
	int			keys[1024];

	char		*path_text_north;
	char		*path_text_south;
	char		*path_text_west;
	char		*path_text_east;

	mlx_color	color_floor;
	mlx_color	color_ceiling;

	char		**map_tmp;

	int			map_width;
	int			map_height;

	void		*tex_north;
	void		*tex_south;
	void		*tex_east;
	void		*tex_west;
}				t_data;

typedef struct s_view
{
	int	width;
	int	height;
}		t_view;

typedef struct s_mlx
{
	mlx_context	mlx;
	mlx_window	window;
	mlx_image	image;
}				t_mlx;

typedef struct s_game
{
	t_data	data;
	t_mlx	mlx;
	t_view	view;
}			t_game;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	int		hit;
}			t_ray;

typedef struct s_perp
{
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}			t_perp;

typedef struct s_draw
{
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
	void		*current_tex;
	int			y;
	int			tex_width;
	int			tex_height;
	mlx_color	color;
}			t_draw;

#endif