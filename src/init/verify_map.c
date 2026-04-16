/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:26:00 by masenche          #+#    #+#             */
/*   Updated: 2026/04/16 17:11:49 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_char(char c, int *spawn)
{
	if (c == '0' || c == '1' || ft_isspace(c))
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		(*spawn)++;
		return (1);
	}
	return (0);
}

static int	verify_char_map(t_game *game)
{
	int	i;
	int	j;
	int	spawn;

	i = 0;
	spawn = 0;
	while (game->data.map_tmp && game->data.map_tmp[i])
	{
		j = 0;
		while (game->data.map_tmp[i][j])
		{
			if (!is_valid_char(game->data.map_tmp[i][j], &spawn))
				return (1);
			j++;
		}
		i++;
	}
	if (spawn != 1)
		return (1);
	return (0);
}

static int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	verify_border(t_game *game)
{
	int		i;
	int		j;

	i = -1;
	while (game->data.map_tmp[++i])
	{
		j = -1;
		while (game->data.map_tmp[i][++j])
		{
			if (is_walkable(game->data.map_tmp[i][j]))
			{
				if (i == 0 || j >= (int)ft_strlen(game->data.map_tmp[i - 1])
					|| ft_isspace(game->data.map_tmp[i - 1][j])
					|| game->data.map_tmp[i +1] == NULL
					|| j >= (int)ft_strlen(game->data.map_tmp[i + 1])
					|| ft_isspace(game->data.map_tmp[i + 1][j])
					|| j == 0 || ft_isspace(game->data.map_tmp[i][j - 1])
					|| game->data.map_tmp[i][j + 1] == '\0'
					|| ft_isspace(game->data.map_tmp[i][j + 1]))
					return (1);
			}
		}
	}
	return (0);
}

int	verify_map(t_game *game)
{
	if (verify_char_map(game))
	{
		ft_free_init(game, "Invalid map");
		return (1);
	}
	if (verify_border(game))
	{
		ft_free_init(game, "Invalid map");
		return (1);
	}
	return (0);
}
