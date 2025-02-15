/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:17:05 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/15 02:29:00 by alibabab         ###   ########.fr       */
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
		if (map[i][j] != '1')
			err_msg("Map must be surrounded by walls\n", data);
		j = ft_strlen(map[i]) - 1;
		while (j >= 0 && ft_isspace(map[i][j]))
			j--;
		if (map[i][j] != '1')
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
