/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:26:56 by masenche          #+#    #+#             */
/*   Updated: 2026/04/04 13:08:11 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

#include "../mlx/includes/mlx.h"

typedef struct s_data
{
	double	posX; //x start position
	double	posY; //y start position
	double	dirX; //initial direction vector
	double	dirY; //initial direction vector
	double	planeX; //the 2d raycaster version of camera plane
	double	planeY; //the 2d raycaster version of camera plane
	double	time; //time of current frame
	double	oldTime; //time of previous frame
	int     **map;
	int keys[1024];
}			t_data;

typedef struct s_view
{
	int	width;
	int	height;
}		t_view;

typedef struct s_mlx
{
	mlx_context mlx;
	mlx_window window;
	mlx_image image;
}			t_mlx;

typedef struct s_game
{
	t_data	data;
	t_mlx	mlx;
	t_view	view;
}			t_game;

typedef struct s_ray {
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	int		stepX;
	int		stepY;
	int		side;
	int		hit;
} 			t_ray;

typedef struct s_perp
{
	double	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
}			t_perp;


#endif