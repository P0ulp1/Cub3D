/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:11:32 by alibabab          #+#    #+#             */
/*   Updated: 2025/03/18 11:15:10 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_declarations(int *counts, t_data *data, char **to_free)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (counts[i] != 1)
		{
			free_split(to_free);
			err_msg("Component must be declared exactly once\n", data);
		}
		i++;
	}
}

void	check_declarations(char **lines, t_data *data)
{
	int	counts[6];
	int	i;

	i = -1;
	while (++i < 6)
		counts[i] = 0;
	i = 0;
	while (lines[i])
	{
		if (ft_strstr(lines[i], "NO "))
			counts[0]++;
		else if (ft_strstr(lines[i], "SO "))
			counts[1]++;
		else if (ft_strstr(lines[i], "WE "))
			counts[2]++;
		else if (ft_strstr(lines[i], "EA "))
			counts[3]++;
		else if (ft_strstr(lines[i], "F "))
			counts[4]++;
		else if (ft_strstr(lines[i], "C "))
			counts[5]++;
		i++;
	}
	validate_declarations(counts, data, lines);
}

void	check_textures_exist(t_data *data)
{
	if (!data->scene->north_texture || !data->scene->south_texture
		|| !data->scene->west_texture || !data->scene->east_texture)
		err_msg("Missing texture or color declaration\n", data);
	if (data->has_door)
	{
		if (!data->scene->door_texture)
			err_msg("Missing door texture declaration\n", data);
	}
}

void	check_character(t_data *data)
{
	int	player_count;
	int	i;
	int	j;

	player_count = 0;
	i = -1;
	while (data->scene->map[++i])
	{
		j = -1;
		while (data->scene->map[i][++j])
		{
			if (ft_strchr("NSEW", data->scene->map[i][j]))
			{
				player_count++;
				init_player(data, i, j, data->scene->map[i][j]);
			}
			else if (ft_strchr("D", data->scene->map[i][j]))
				data->has_door = 1;
			else if (!ft_strchr("01D ", data->scene->map[i][j]))
				err_msg("Invalid character in map\n", data);
		}
	}
	if (player_count != 1)
		err_msg("Map must contain exactly one player\n", data);
}
