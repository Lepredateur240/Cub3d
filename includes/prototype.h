/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:27:10 by masenche          #+#    #+#             */
/*   Updated: 2026/04/18 13:56:21 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROTOTYPE_H
# define PROTOTYPE_H

#include "libft.h"
// Prototypes for all functions used in the project

//error
//error.c
void	ft_perror(const char *message);
void	ft_free_init(t_game *game, char *error);

//event
//keyhook.c
void	key_hook_up(int keycode, void *param);
void	key_hook_down(int keycode, void *param);
void	update_player(t_game *game);
// mlx_event.c
void	run_game_loop(t_game *game);
void	cleanup_and_exit(t_game *game);

//gnl
//gnl.c
char	*get_next_line(int fd);

// init
//copy_map.c
int copy_map(t_game *game);
//handle_map.c
int handle_map(t_game *game, char* line);
// init_image.c
void	init_image(t_game *game, t_ray *ray, t_perp *perp, int x);
void	load_textures(t_game *game);
// init_mlx.c
void	init_mlx(char** argv, t_game *game);
//map_color.c
int handle_color(t_game *game, char* line);
//map_texture.c
int handle_texture(t_game *game, char* line);
//map.c
int init_map(char** argv, t_game *game);
// spawn.c
void spawn_player(t_game *game, double x, double y, char o);
//verify_map.c
int verify_map(t_game *game);


// /raycasting
// draw.c
void	draw_textured_line(t_game *game, t_ray *ray, t_perp *perp, int x);
// to_3d.c
void	to_3d(t_game *game);

//main.c
void	render_frame(void *param);
void 	render_loop(void *param);

#endif