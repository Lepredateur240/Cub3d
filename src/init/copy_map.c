/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:26:00 by masenche          #+#    #+#             */
/*   Updated: 2026/04/16 11:21:18 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	height_width(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->data.map_tmp[i])
	{
		j = 0;
		while (game->data.map_tmp[i][j] && game->data.map_tmp[i][j] != '\n')
			j++;
		if (j > game->data.map_width)
			game->data.map_width = j;
		i++;
	}
	game->data.map_height = i;
}

static int	alloc_map(t_game *game)
{
	int	i;

	game->data.map = malloc(sizeof(int *) * (game->data.map_height + 1));
	if (!game->data.map)
		return (1);
	i = 0;
	while (i < game->data.map_height)
	{
		game->data.map[i] = malloc(sizeof(int) * game->data.map_width);
		if (!game->data.map[i])
		{
			while (--i >= 0)
				free(game->data.map[i]);
			free(game->data.map);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	tmp_to_int(t_game *game)
{
	int	i;
	int	j;
	int	line_len;

	i = -1;
	while (++i < game->data.map_height)
	{
		j = -1;
		line_len = ft_strlen(game->data.map_tmp[i]);
		while (++j < game->data.map_width)
		{
			game->data.map[i][j] = 1;
			if (j < line_len && game->data.map_tmp[i][j] == '0')
				game->data.map[i][j] = 0;
			else if (j < line_len
				&& ft_strchr("NSEW", game->data.map_tmp[i][j]))
			{
				spawn_player(game, (double)j, (double)i,
					game->data.map_tmp[i][j]);
				game->data.map[i][j] = 0;
			}
		}
	}
	game->data.map[i] = NULL;
	return (0);
}

int	copy_map(t_game *game)
{
	height_width(game);
	if (alloc_map(game))
		return (1);
	if (tmp_to_int(game))
		return (1);
	return (0);
}
