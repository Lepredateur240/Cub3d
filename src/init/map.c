/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:26:00 by masenche          #+#    #+#             */
/*   Updated: 2026/04/20 14:54:02 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	verify_cub_file(char *path, int *fd)
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

static int	is_empty_line(char *line)
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

static int	parse_line(t_game *game, char *line, int *map)
{
	int	line_len;
	int	ret;

	line_len = ft_strlen(line);
	ret = 0;
	if (*map == 0 && is_empty_line(line))
		return (0);
	if (*map == 0 && (ft_strnstr(line, "NO", line_len)
			|| ft_strnstr(line, "SO", line_len)
			|| ft_strnstr(line, "WE", line_len)
			|| ft_strnstr(line, "EA", line_len)))
		ret = handle_texture(game, line);
	else if (*map == 0 && (ft_strnstr(line, "F", line_len)
			|| ft_strnstr(line, "C", line_len)))
		ret = handle_color(game, line);
	else
	{
		*map = 1;
		ret = handle_map(game, line);
	}
	return (ret);
}

static int	read_cub_file(t_game *game, int fd)
{
	char	*line;
	int		map;

	map = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (parse_line(game, line, &map))
		{
			free(line);
			get_next_line(-1);
			return (1);
		}
		free(line);
	}
	if (!game->data.path_text_north || !game->data.path_text_south
		|| !game->data.path_text_east || !game->data.path_text_west)
	{
		ft_free_init(game, "Invalid setting");
		return (1);
	}
	return (0);
}

int	init_map(char **argv, t_game *game)
{
	int	fd;

	if (verify_cub_file(argv[1], &fd))
		return (1);
	if (read_cub_file(game, fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	if (verify_map(game))
		return (1);
	if (copy_map(game))
		return (1);
	return (0);
}
