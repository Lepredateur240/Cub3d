/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:26:00 by masenche          #+#    #+#             */
/*   Updated: 2026/04/15 12:12:22 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int is_valid_char(char c, int *spawn)
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

static int verify_char_map(t_game *game)
{
	int	i;
	int	j;
	int	spawn;

	i = 0;
	spawn = 0;
	while (game->data.map_tmp[i])
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

// static int verify_border(t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (game->data.map_tmp[i])
// 	{
// 		j = 0;
// 		while (game->data.map_tmp[i][j])
// 		{
			
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int verify_map(t_game *game)
{
	if (verify_char_map(game))
		return (1);

	// if (verify_border(game))
	// 	return (1);

	return (0);
}
