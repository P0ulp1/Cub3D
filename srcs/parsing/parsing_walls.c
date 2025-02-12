/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:17:05 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/12 21:30:07 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_horizontal_borders(char **map)
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
			err_msg("Map must be surrounded by walls\n");
		i++;
	}
	i = 0;
	while (map[height - 1][i])
	{
		if (map[height - 1][i] != '1' && !ft_isspace(map[height - 1][i]))
			err_msg("Map must be surrounded by walls\n");
		i++;
	}
}

static void	check_vertical_borders(char **map)
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
		if (map[i][j] != '1')
			err_msg("Map must be surrounded by walls\n");
		j = ft_strlen(map[i]) - 1;
		while (j >= 0 && ft_isspace(map[i][j]))
			j--;
		if (map[i][j] != '1')
			err_msg("Map must be surrounded by walls\n");
		i++;
	}
}

static void	check_inner_walls(char **map)
{
	int	height;
	int	i;
	int	j;

	height = 0;
	while (map[height])
		height++;
	i = 1;
	while (i < height - 1)
	{
		j = 1;
		while (j < (int)ft_strlen(map[i]) - 1)
		{
			if (map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '\t')
			{
				if (ft_isspace(map[i - 1][j]) || ft_isspace(map[i + 1][j])
					|| ft_isspace(map[i][j - 1]) || ft_isspace(map[i][j + 1]))
					err_msg("Map must be surrounded by walls\n");
			}
			j++;
		}
		i++;
	}
}

void	check_wall(char **map)
{
	check_horizontal_borders(map);
	check_vertical_borders(map);
	check_inner_walls(map);
}
