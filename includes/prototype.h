/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:27:10 by masenche          #+#    #+#             */
/*   Updated: 2026/04/05 20:38:46 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPE_H
# define PROTOTYPE_H

#include "libft.h"
// Prototypes for all functions used in the project

// /error
// ft_perror.c
// Error handling
void	ft_perror(const char *message);


// /init
// init_mlx.c
// Initialization
void	init_mlx(t_game *game);

// init_image.c
void	init_image(t_game *game, t_ray *ray, t_perp *perp, int x);
void	load_textures(t_game *game);

// map.c
// Map
void init_map(t_game *game);

// spawn.c
// Player spawning
void spawn_player(t_game *game, double x, double y, char o);

// /on_event
// mlx_event.c
// Game loop
void	run_game_loop(t_game *game);
void	cleanup_and_exit(t_game *game);
void	window_hook(int event, void *param);


// keyhook
// keyhook.c
// Key event handling
void	key_hook_up(int keycode, void *param);
void	key_hook_down(int keycode, void *param);
void	update_player(t_game *game);

// /raystracing
// to_3d.c
// Raycasting and 3D projection
void	to_3d(t_game *game);

// draw.c
// Drawing functions
void	draw_textured_line(t_game *game, t_ray *ray, t_perp *perp, int x);

//main.c
// Main entry point
void	render_frame(void *param);
void 	render_loop(void *param);

#endif