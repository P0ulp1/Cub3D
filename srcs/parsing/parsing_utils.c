/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:21:46 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/14 22:58:02 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_color(char *line, int *color, t_data *data, char **to_free)
{
	char	**str;
	int		i;

	str = ft_split(line, ',');
	if (!str || !str[0] || !str[1] || !str[2])
	{
		free_split(to_free);
		free_split(str);
		err_msg("Invalid color format\n", data);
	}
	color[0] = ft_atoi(str[0]);
	color[1] = ft_atoi(str[1]);
	color[2] = ft_atoi(str[2]);
	free_split(str);
	i = -1;
	while (++i < 3)
	{
		if (color[i] < 0 || color[i] > 255)
		{
			free_split(to_free);
			err_msg("Color values must be between 0 and 255\n", data);
		}
	}
}

void	parse_textures(char *line, t_data *data, char **to_free)
{
	while (ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		data->scene->north_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		data->scene->south_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		data->scene->west_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		data->scene->east_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "DOOR ", 3) == 0)
		data->scene->east_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(line + 2, data->scene->floor_color, data, to_free);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(line + 2, data->scene->ceiling_color, data, to_free);
}

void	parse_map(char **lines, int start, t_data *data)
{
	int	i;
	int	map_height;
	int	j;

	i = start;
	map_height = 0;
	while (lines[i])
	{
		map_height++;
		i++;
	}
	data->scene->map = malloc(sizeof(char *) * (map_height + 1));
	if (!data->scene->map)
		err_msg("Memory allocation failed\n", data);
	i = start;
	j = 0;
	while (lines[i])
	{
		data->scene->map[j] = ft_strdup(lines[i]);
		if (!data->scene->map[j])
			err_msg("Memory allocation failed\n", data);
		i++;
		j++;
	}
	data->scene->map[j] = NULL;
}
