/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:06:33 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/13 01:14:10 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	read_and_join(int fd, char **content, char *buffer)
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
			err_msg("Memory allocation failed\n");
		}
		*content = tmp;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
	{
		free(*content);
		err_msg("Read error\n");
	}
}

char	*read_file(int fd)
{
	char	*buffer;
	char	*content;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		err_msg("Memory allocation failed\n");
	content = ft_strdup("");
	if (!content)
	{
		free(buffer);
		err_msg("Memory allocation failed\n");
	}
	read_and_join(fd, &content, buffer);
	free(buffer);
	return (content);
}

static int	is_declaration(char *line)
{
	return (!ft_strstr(line, "NO ") && !ft_strstr(line, "SO ")
		&& !ft_strstr(line, "WE ") && !ft_strstr(line, "EA ")
		&& !ft_strstr(line, "F ") && !ft_strstr(line, "C "));
}

static void	parse_scene(char *content, t_scene *scene)
{
	char	**lines;
	int		i;

	lines = ft_split(content, '\n');
	check_declarations(lines);
	i = 0;
	while (lines[i])
	{
		while (lines[i] && (lines[i][0] == '\0' || ft_str_isspace(lines[i])))
			i++;
		if (lines[i] && ft_strchr(lines[i], '1') && is_declaration(lines[i]))
		{
			parse_map(lines, i, scene);
			break ;
		}
		else
			parse_textures(lines[i], scene);
		i++;
	}
	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
	check_character(scene);
}

void	parsing(char *file, t_data *data)
{
	int		fd;
	char	*content;

	if (ft_strlen(file) < 4)
		err_msg("Invalid file extension\n");
	if (ft_strcmp(file + ft_strlen(file) - 4, ".cub"))
		err_msg("Invalid file extension\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		err_msg("Cannot open file\n");
	content = read_file(fd);
	close(fd);
	data->scene = malloc(sizeof(t_scene));
	if (!data->scene)
		err_msg("Memory allocation failed\n");
	parse_scene(content, data->scene);
	free(content);
}
