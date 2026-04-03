/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:32:04 by masenche          #+#    #+#             */
/*   Updated: 2026/04/03 19:00:00 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include "../mlx/includes/mlx.h"

# define COLOR_WHITE    (mlx_color){.rgba = 0xFFFFFFFF}
# define COLOR_BLACK    (mlx_color){.rgba = 0x000000FF}
# define COLOR_RED      (mlx_color){.rgba = 0xFF0000FF}
# define COLOR_GREEN    (mlx_color){.rgba = 0x00FF00FF}
# define COLOR_BLUE     (mlx_color){.rgba = 0x0000FFFF}

/* --- Couleurs Cub3D (Ambiance) --- */
# define COLOR_CEILING  (mlx_color){.rgba = 0x323232FF}    /* Gris foncé */
# define COLOR_FLOOR    (mlx_color){.rgba = 0x646464FF} /* Gris clair */

/* --- Couleurs de Murs (Effet d'ombrage) --- */
// Face Est/Ouest (Pleine lumière)
# define WALL_LIGHT     (mlx_color){.rgba = 0xC8C8C8FF} 
// Face Nord/Sud (Ombragé)
# define WALL_SHADOW    (mlx_color){.rgba = 0x646464FF}

#endif