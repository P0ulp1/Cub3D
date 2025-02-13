/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:06:33 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/13 16:20:14 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	read_and_join(int fd, char **content, char *buffer, t_data *data)
{
	char	*tmp;
	int		bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(*content, buffer);
		free(*content);
		if (!tmp)
		{
			free(buffer);
			err_msg("Memory allocation failed\n", data);
		}
		*content = tmp;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
	{
		free(*content);
		err_msg("Read error\n", data);
	}
}

char	*read_file(int fd, t_data *data)
{
	char	*buffer;
	char	*content;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		err_msg("Memory allocation failed\n", data);
	content = ft_strdup("");
	if (!content)
	{
		free(buffer);
		err_msg("Memory allocation failed\n", data);
	}
	read_and_join(fd, &content, buffer, data);
	free(buffer);
	return (content);
}

static int	is_declaration(char *line)
{
	return (!ft_strstr(line, "NO ") && !ft_strstr(line, "SO ")
		&& !ft_strstr(line, "WE ") && !ft_strstr(line, "EA ")
		&& !ft_strstr(line, "F ") && !ft_strstr(line, "C "));
}

static void	parse_scene(char *content, t_data *data)
{
	char	**lines;
	int		i;

	lines = ft_split(content, '\n');
	free(content);
	check_declarations(lines, data);
	i = -1;
	while (lines[++i])
	{
		while (lines[i] && (lines[i][0] == '\0' || ft_str_isspace(lines[i])))
			i++;
		if (lines[i] && ft_strchr(lines[i], '1') && is_declaration(lines[i]))
		{
			parse_map(lines, i, data);
			break ;
		}
		else
			parse_textures(lines[i], data, lines);
	}
	free_split(lines);
	if (!data->scene->map)
		err_msg("No map found in the file\n", data);
}

void	parsing(char *file, t_data *data)
{
	int		fd;
	char	*content;

	init_data(data);
	if (ft_strlen(file) < 4)
		err_msg("Invalid file extension\n", data);
	if (ft_strcmp(file + ft_strlen(file) - 4, ".cub"))
		err_msg("Invalid file extension\n", data);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		err_msg("Cannot open file\n", data);
	content = read_file(fd, data);
	close(fd);
	parse_scene(content, data);
	check_wall(data->scene->map, data);
	check_character(data);
	check_textures_files(data);
}
