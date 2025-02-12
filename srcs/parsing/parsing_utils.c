/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 21:21:46 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/12 21:31:10 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	parse_color(char *line, int *color)
{
	char	**str;
	int		i;

	str = ft_split(line, ',');
	if (!str || !str[0] || !str[1] || !str[2])
		err_msg("Invalid color format\n");
	color[0] = ft_atoi(str[0]);
	color[1] = ft_atoi(str[1]);
	color[2] = ft_atoi(str[2]);
	i = 0;
	while (i < 3)
	{
		if (color[i] < 0 || color[i] > 255)
			err_msg("Color values must be between 0 and 255\n");
		i++;
	}
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	parse_textures(char *line, t_scene *scene)
{
	while (ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0)
		scene->north_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		scene->south_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		scene->west_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		scene->east_texture = ft_strdup(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		parse_color(line + 2, scene->floor_color);
	else if (ft_strncmp(line, "C ", 2) == 0)
		parse_color(line + 2, scene->ceiling_color);
}

void	parse_map(char **lines, int start, t_scene *scene)
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
	scene->map = malloc(sizeof(char *) * (map_height + 1));
	if (!scene->map)
		err_msg("Memory allocation failed\n");
	i = start;
	j = 0;
	while (lines[i])
	{
		scene->map[j] = ft_strdup(lines[i]);
		if (!scene->map[j])
			err_msg("Memory allocation failed\n");
		i++;
		j++;
	}
	scene->map[j] = NULL;
}
