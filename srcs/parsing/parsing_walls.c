/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:17:05 by alibabab          #+#    #+#             */
/*   Updated: 2025/04/05 11:44:06 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_horizontal_borders(char **map, t_data *data)
{
	int	height;
	int	i;

	height = 0;
	while (map[height])
		height++;
	i = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1' && !ft_isspace(map[0][i]))
			err_msg("Map must be surrounded by walls\n", data);
		i++;
	}
	i = 0;
	while (map[height - 1][i])
	{
		if (map[height - 1][i] != '1' && !ft_isspace(map[height - 1][i]))
			err_msg("Map must be surrounded by walls\n", data);
		i++;
	}
}

static void	check_vertical_borders(char **map, t_data *data)
{
	int	height;
	int	i;
	int	j;

	height = 0;
	while (map[height])
		height++;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (ft_isspace(map[i][j]))
			j++;
		if (map[i][j] && map[i][j] != '1')
			err_msg("Map must be surrounded by walls\n", data);
		j = ft_strlen(map[i]) - 1;
		while (j >= 0 && ft_isspace(map[i][j]))
			j--;
		if (j >= 0 && map[i][j] && map[i][j] != '1')
			err_msg("Map must be surrounded by walls\n", data);
		i++;
	}
}

static void	check_inner_walls(char **map, t_data *data)
{
	int	i;
	int	j;
	int	height;

	height = 0;
	while (map[height])
		height++;
	i = 1;
	while (i < height - 1)
	{
		j = 1;
		while (j < (int)ft_strlen(map[i]) - 1)
		{
			if (map[i][j] != '1' && !ft_isspace(map[i][j])
				&& (j >= (int)ft_strlen(map[i - 1]) || ft_isspace(map[i - 1][j])
					|| j >= (int)ft_strlen(map[i + 1]) || ft_isspace(map[i
						+ 1][j]) || ft_isspace(map[i][j - 1])
					|| ft_isspace(map[i][j + 1])))
				err_msg("Map must be surrounded by walls\n", data);
			j++;
		}
		i++;
	}
}

void	check_wall(char **map, t_data *data)
{
	check_horizontal_borders(map, data);
	check_vertical_borders(map, data);
	check_inner_walls(map, data);
}

void	check_empty_line(char *content, t_data *data)
{
	int		i;
	int		in_map;
	char	*line;

	in_map = 0;
	line = content;
	i = -1;
	while (content[++i])
	{
		if (content[i] == '\n')
		{
			content[i] = '\0';
			while (ft_isspace(*line))
				line++;
			if (*line && is_not_declaration(line))
				in_map = 1;
			if (in_map && *line == '\0')
			{
				free(content);
				err_msg("Invalid line in the map\n", data);
			}
			content[i] = '\n';
			line = content + i + 1;
		}
	}
}
