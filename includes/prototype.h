/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototype.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:27:10 by masenche          #+#    #+#             */
/*   Updated: 2026/04/01 17:44:49 by masenche         ###   ########.fr       */
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

// map.c
// Map
extern int worldmap[24][24];


// /on_event
// mlx_event.c
// Game loop
void run_game_loop(t_game *game);

#endif