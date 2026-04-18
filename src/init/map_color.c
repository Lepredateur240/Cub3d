/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algasnie <algasnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 15:26:00 by masenche          #+#    #+#             */
/*   Updated: 2026/04/18 13:49:36 by algasnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	verify_split(char **split)
{
	int	count;
	int	len;
	int	numb;

	count = 0;
	while (split[count])
	{
		len = ft_strlen(split[count]);
		if (count > 3)
			return (1);
		numb = ft_atoi(split[count]);
		if (numb < 0 || numb > 255)
			return (1);
		count++;
	}
	if (count != 3)
		return (1);
	return (0);
}

static int	verify_color(char *color)
{
	int	commas;
	int	i;

	i = 0;
	commas = 0;
	while (color[i])
	{
		if (color[i] == ',')
			commas++;
		if (!ft_isdigit(color[i]) && color[i] != ',')
			return (1);
		i++;
	}
	return (commas != 2);
}

static int	set_color(t_game *game, char *color, char *key)
{
	mlx_color	*target;
	char		**split;

	if (!color || verify_color(color))
		return (1);
	if (ft_strncmp(key, "F", 1) == 0)
		target = &game->data.color_floor;
	else
		target = &game->data.color_ceiling;
	split = ft_split(color, ',');
	if (!split)
		return (1);
	if (verify_split(split))
	{
		ft_ultimate_free("%a", &split);
		return (1);
	}
	target->r = ft_atoi(split[0]);
	target->g = ft_atoi(split[1]);
	target->b = ft_atoi(split[2]);
	target->a = 255;
	ft_ultimate_free("%a", &split);
	return (0);
}

static void	handle_color_param(t_game *game, char *line, char *key, int *error)
{
	int		i;
	int		j;
	char	*color;

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
	color = ft_substr(line, i, j - i);
	while (line[j] && ft_isspace(line[j]))
		j++;
	if (line[j] && line[j] != '\n')
	{
		free(color);
		return ;
	}
	*error = set_color(game, color, key);
	free(color);
}

int	handle_color(t_game *game, char *line)
{
	int	i;
	int	error;

	i = 0;
	error = 1;
	while (ft_isspace(line[i]))
		i++;
	if (ft_strncmp(&line[i], "F", 1) == 0)
		handle_color_param(game, &line[i + 1], "F", &error);
	else if (ft_strncmp(&line[i], "C", 1) == 0)
		handle_color_param(game, &line[i + 1], "C", &error);
	if (error == 1)
	{
		ft_free_init(game, "Invalid color setting");
		return (1);
	}
	return (0);
}
