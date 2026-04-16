/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:26:00 by masenche          #+#    #+#             */
/*   Updated: 2026/04/16 10:28:34 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int verify_cub_file(char* path, int *fd)
{
	size_t	len_path;

	len_path = ft_strlen(path);
	if (len_path < 5 || ft_strncmp(path + len_path - 4, ".cub", 4) != 0)
	{
		write(2, "Error\nInvalid file extension\n", 30);
		return (1);
	}
	
	*fd = open(path, O_RDONLY);
	if (*fd == -1)
	{
		write(2, "Error\nCould not open map file\n", 31);
		return (1);
	}
	return (0);
}

static int is_empty_line(char *line)
{
	int	i;
	
	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

static int read_cub_file(t_game *game, int fd)
{
	char* line;
	int		map;
	int 	line_len;
	
	map = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line_len = ft_strlen(line);
		if (is_empty_line(line) && map == 0)
		{
			free(line);
			continue ;
		}
		else if (map == 0 && (ft_strnstr(line, "NO", line_len) || ft_strnstr(line, "SO", line_len) || ft_strnstr(line, "WE", line_len) || ft_strnstr(line, "EA", line_len)))
		{
			if (handle_texture(game, line))
					return (1);
		}
		else if (map == 0 && (ft_strnstr(line, "F", line_len) || ft_strnstr(line, "C", line_len) ))
		{
			if (handle_color(game, line))
				return (1);
		}
		else
		{
			map = 1;
			if (handle_map(game, line))
				return (1);
		}
		free(line);
	}
	return (0);
}

int init_map(char** argv, t_game *game)
{
	int fd;
	
	if (verify_cub_file(argv[1], &fd))
		return (1);

	if (read_cub_file(game, fd))
		return (1);

	if (verify_map(game))
		return (1);

	if (copy_map(game))
		return (1);

	printf("north: %s\nsouth: %s\nwest: %s\neast: %s\n", game->data.path_text_north, game->data.path_text_south, game->data.path_text_west, game->data.path_text_east);
	printf("ceilling: %d,%d,%d\n", game->data.color_ceiling.r, game->data.color_ceiling.g, game->data.color_ceiling.b);
	printf("floor: %d,%d,%d\n", game->data.color_floor.r, game->data.color_floor.g, game->data.color_floor.b);

	int i = 0;

	while (game->data.map_tmp[i])
	{
		printf("%s", game->data.map_tmp[i]);
		i++;
	}
	printf("\n\n");

	int j;

	i = 0;
	while (game->data.map[i])
	{
		j = 0;
		while (j < game->data.map_width)
		{
			printf("%d", game->data.map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	return (0);
}
