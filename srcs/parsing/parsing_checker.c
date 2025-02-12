/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checker.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:11:32 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/12 21:59:21 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_declarations(int *counts)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (counts[i] != 1)
			err_msg("Component must be declared exactly once\n");
		i++;
	}
}

void	check_declarations(char **lines)
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
	validate_declarations(counts);
}

static void	check_textures_files(t_scene *scene)
{
	int	fd;

	if (!scene->north_texture || !scene->south_texture || !scene->west_texture
		|| !scene->east_texture)
		err_msg("Missing texture file\n");
	fd = open(scene->north_texture, O_RDONLY);
	if (fd < 0)
		err_msg("Cannot open north texture file\n");
	close(fd);
	fd = open(scene->south_texture, O_RDONLY);
	if (fd < 0)
		err_msg("Cannot open south texture file\n");
	close(fd);
	fd = open(scene->west_texture, O_RDONLY);
	if (fd < 0)
		err_msg("Cannot open west texture file\n");
	close(fd);
	fd = open(scene->east_texture, O_RDONLY);
	if (fd < 0)
		err_msg("Cannot open east texture file\n");
	close(fd);
}

void	check_character(t_scene *scene)
{
	int	player_count;
	int	i;
	int	j;

	if (!scene->map)
		err_msg("No map found in the file\n");
	player_count = 0;
	check_wall(scene->map);
	i = 0;
	while (scene->map[i])
	{
		j = 0;
		while (scene->map[i][j])
		{
			if (ft_strchr("N", scene->map[i][j]))
				player_count++;
			else if (!ft_strchr("01 ", scene->map[i][j]))
				err_msg("Invalid character in map\n");
			j++;
		}
		i++;
	}
	if (player_count != 1)
		err_msg("Map must contain exactly one player start position\n");
	check_textures_files(scene);
}
