/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:26:00 by masenche          #+#    #+#             */
/*   Updated: 2026/04/16 11:23:21 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_line(char **map_tmp)
{
	int	i;

	i = 0;
	if (!map_tmp)
		return (i);
	while (map_tmp[i])
		i++;
	return (i);
}

int	save_map_tmp(t_game *game, char *line)
{
	int		nb_line;
	int		i;
	char	**new_tab;

	nb_line = count_line(game->data.map_tmp);
	new_tab = malloc(sizeof(char *) * (nb_line + 2));
	if (!new_tab)
		return (1);
	i = 0;
	while (i < nb_line)
	{
		new_tab[i] = game->data.map_tmp[i];
		i++;
	}
	new_tab[i] = ft_strdup(line);
	if (!new_tab[i])
	{
		free(new_tab);
		return (1);
	}
	new_tab[i + 1] = NULL;
	free(game->data.map_tmp);
	game->data.map_tmp = new_tab;
	return (0);
}

int	handle_map(t_game *game, char *line)
{
	if (line)
	{
		if (save_map_tmp(game, line))
			return (1);
	}
	return (0);
}
