/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:06:33 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/12 22:04:00 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*read_file(int fd)
{
	char	*content;
	char	*line;
	size_t	total_size;
	size_t	allocated_size;
	char	*new_content;
	size_t	line_len;

	total_size = 0;
	allocated_size = 1024;
	content = malloc(allocated_size);
	if (!content)
		err_msg("Memory allocation failed\n");
	content[0] = '\0';
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_len = ft_strlen(line);
		while (total_size + line_len + 1 > allocated_size)
		{
			allocated_size *= 2;
			new_content = malloc(allocated_size);
			if (!new_content)
			{
				free(content);
				err_msg("Memory allocation failed\n");
			}
			ft_strcpy(new_content, content);
			free(content);
			content = new_content;
		}
		ft_strcat(content, line);
		total_size += line_len;
		free(line);
		line = get_next_line(fd);
	}
	if (total_size == 0)
	{
		free(content);
		err_msg("Failed to read file\n");
	}
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
