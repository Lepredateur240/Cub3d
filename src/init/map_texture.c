/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:26:00 by masenche          #+#    #+#             */
/*   Updated: 2026/04/16 11:26:33 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_texture_path(t_game *game, char *path, char *key)
{
	char	**target;

	target = NULL;
	if (strncmp(key, "NO", 2) == 0)
		target = &game->data.path_text_north;
	else if (strncmp(key, "SO", 2) == 0)
		target = &game->data.path_text_south;
	else if (strncmp(key, "WE", 2) == 0)
		target = &game->data.path_text_west;
	else if (strncmp(key, "EA", 2) == 0)
		target = &game->data.path_text_east;
	if (target && !*target)
	{
		*target = path;
		return (0);
	}
	else
		return (1);
}

static void	handle_texture_path(t_game *game, char *line, char *key, int *error)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	if (!ft_isspace(line[i]))
		return ;
	while (line[i] && ft_isspace(line[i]))
		i++;
	j = i;
	while (line[j] && !ft_isspace(line[j]))
		j++;
	if (line[i] == '\n' || line[i] == '\0')
		return ;
	path = ft_substr(line, i, j - i);
	if (!path)
		return ;
	while (line[j] && ft_isspace(line[j]))
		j++;
	if (line[j] && line[j] != '\n')
		return ;
	if (set_texture_path(game, path, key))
		*error = 1;
	else
		*error = 0;
}

int	handle_texture(t_game *game, char *line)
{
	int	i;
	int	error;

	i = 0;
	error = 1;
	while (ft_isspace(line[i]))
		i++;
	if (strncmp(&line[i], "NO", 2) == 0)
		handle_texture_path(game, &line[i + 2], "NO", &error);
	else if (strncmp(&line[i], "SO", 2) == 0)
		handle_texture_path(game, &line[i + 2], "SO", &error);
	else if (strncmp(&line[i], "WE", 2) == 0)
		handle_texture_path(game, &line[i + 2], "WE", &error);
	else if (strncmp(&line[i], "EA", 2) == 0)
		handle_texture_path(game, &line[i + 2], "EA", &error);
	if (error == 1)
	{
		write(2, "Error\nInvalid setting\n", 23);
		return (1);
	}
	return (0);
}
