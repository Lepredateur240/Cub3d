/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 16:25:26 by masenche          #+#    #+#             */
/*   Updated: 2026/04/18 13:29:17 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_perror(const char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	ft_free_init(t_game *game, char *error)
{
	if (error)
	{
		write(2, "Error\n", 7);
		write(2, error, ft_strlen(error));
		write(2, "\n", 1);
	}
	if (game->data.path_text_north)
		free(game->data.path_text_north);
	if (game->data.path_text_south)
		free(game->data.path_text_south);
	if (game->data.path_text_east)
		free(game->data.path_text_east);
	if (game->data.path_text_west)
		free(game->data.path_text_west);
	if (game->data.map_tmp)
		ft_ultimate_free("%a", &game->data.map_tmp);
	if (game->data.map)
		ft_ultimate_free("%i", &game->data.map);
}
