/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masenche <masenche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 18:25:37 by masenche          #+#    #+#             */
/*   Updated: 2026/04/05 18:32:23 by masenche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_game *game)
{
    int width;
    int height;

    // Assure-toi d'avoir un dossier "textures" à la racine de ton projet 
    // avec tes 4 fichiers bien renommés en .jpg
    game->data.tex_north = mlx_new_image_from_file(game->mlx.mlx, "texture/nord.jpg", &width, &height);
    game->data.tex_south = mlx_new_image_from_file(game->mlx.mlx, "texture/sud.jpg", &width, &height);
    game->data.tex_east = mlx_new_image_from_file(game->mlx.mlx, "texture/est.jpg", &width, &height);
    game->data.tex_west = mlx_new_image_from_file(game->mlx.mlx, "texture/ouest.jpg", &width, &height);

    // Sécurité : on vérifie que le chargement a bien fonctionné
    if (!game->data.tex_north || !game->data.tex_south || !game->data.tex_east || !game->data.tex_west)
        ft_perror("Erreur : Impossible de charger les textures JPG");
}

void	init_image(t_game *game, t_ray *ray, t_perp *perp, int x)
{
	int			y;
    mlx_color	color;
	int			wallType;

    // 1. Dessiner le plafond
    y = 0;
    while (y < perp->drawStart)
    {
		mlx_set_image_pixel(game->mlx.mlx, game->mlx.image, x, y, COLOR_CEILING);
        y++;
    }

    // 2. Dessiner le mur
	wallType = game->data.map[ray->mapY][ray->mapX];
	if (wallType == 2)
		color = COLOR_RED;
	else if (wallType == 3)
		color = COLOR_GREEN;
	else if (wallType == 4)
		color = COLOR_BLUE;
	else
    	color = COLOR_WHITE; // Blanc
    if (ray->side == 1)
        color.rgba = 0x7F7F7F; // Gris si face Sud/Nord
    while (y < perp->drawEnd)
    {
        mlx_set_image_pixel(game->mlx.mlx, game->mlx.image, x, y, color); // On utilise bien 'color' ici !
        y++;
    }
    // 3. Dessiner le sol
    while (y < game->view.height)
    {
        mlx_set_image_pixel(game->mlx.mlx, game->mlx.image, x, y, COLOR_FLOOR);
        y++;
    }
}
