/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:21:46 by alibabab          #+#    #+#             */
/*   Updated: 2025/03/18 14:29:55 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_component(char *str, t_data *data, char **to_free,
		char **str_free)
{
	char	*trimmed;
	int		color;

	trimmed = ft_strtrim(str, " \t\n\r\v");
	if (!trimmed || trimmed[0] == '\0' || !is_valid_number(trimmed))
	{
		if (trimmed)
			free(trimmed);
		free_split(str_free);
		free_split(to_free);
		err_msg("Invalid color component\n", data);
	}
	color = ft_atoi(trimmed);
	free(trimmed);
	if (color < 0 || color > 255)
	{
		free_split(str_free);
		free_split(to_free);
		err_msg("Color out of range (0-255)\n", data);
	}
	return (color);
}

static void	parse_color(char *line, int *color, t_data *data, char **to_free)
{
	char	**str;
	int		i;

	str = ft_split(line, ',');
	if (!str || !str[0] || !str[1] || !str[2] || str[3] != NULL)
	{
		free_split(to_free);
		free_split(str);
		err_msg("Invalid color format: 3 values required\n", data);
	}
	i = 0;
	while (i < 3)
	{
		color[i] = parse_component(str[i], data, to_free, str);
		i++;
	}
	free_split(str);
}

void	parse_textures(char *line, t_data *data, char **to_free)
{
	line = ft_skip_space(line);
	if (!ft_strncmp(line, "NO", 2))
		data->scene->north_texture = ft_strdup(ft_skip_space(line + 2));
	else if (!ft_strncmp(line, "SO", 2))
		data->scene->south_texture = ft_strdup(ft_skip_space(line + 2));
	else if (!ft_strncmp(line, "WE", 2))
		data->scene->west_texture = ft_strdup(ft_skip_space(line + 2));
	else if (!ft_strncmp(line, "EA", 2))
		data->scene->east_texture = ft_strdup(ft_skip_space(line + 2));
	else if (!ft_strncmp(line, "DOOR", 4))
		data->scene->door_texture = ft_strdup(ft_skip_space(line + 4));
	else if (!ft_strncmp(line, "F", 1))
		parse_color(ft_skip_space(line + 1), data->scene->floor_color, data,
			to_free);
	else if (!ft_strncmp(line, "C", 1))
		parse_color(ft_skip_space(line + 1), data->scene->ceiling_color, data,
			to_free);
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
