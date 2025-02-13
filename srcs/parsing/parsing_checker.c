/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:11:32 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/13 14:03:19 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_declarations(int *counts, t_data *data)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (counts[i] != 1)
			err_msg("Component must be declared exactly once\n", data);
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
	validate_declarations(counts, data);
}

static void	check_textures_files(t_data *data)
{
	int	fd;

	if (!data->scene->north_texture || !data->scene->south_texture
		|| !data->scene->west_texture || !data->scene->east_texture)
		err_msg("Missing texture file\n", data);
	fd = open(data->scene->north_texture, O_RDONLY);
	if (fd < 0)
		err_msg("Cannot open north texture file\n", data);
	close(fd);
	fd = open(data->scene->south_texture, O_RDONLY);
	if (fd < 0)
		err_msg("Cannot open south texture file\n", data);
	close(fd);
	fd = open(data->scene->west_texture, O_RDONLY);
	if (fd < 0)
		err_msg("Cannot open west texture file\n", data);
	close(fd);
	fd = open(data->scene->east_texture, O_RDONLY);
	if (fd < 0)
		err_msg("Cannot open east texture file\n", data);
	close(fd);
}

void	check_character(t_data *data)
{
	int	player_count;
	int	i;
	int	j;

	check_wall(data->scene->map, data);
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
				if (player_count != 1)
					err_msg("Map must contain exactly one player\n", data);
				init_player(data, i, j, data->scene->map[i][j]);
			}
			else if (!ft_strchr("01 ", data->scene->map[i][j]))
				err_msg("Invalid character in map\n", data);
		}
	}
	check_textures_files(data);
}
