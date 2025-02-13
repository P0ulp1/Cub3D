/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 03:23:57 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/13 14:02:56 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_data *data)
{
	data->scene = malloc(sizeof(t_scene));
	if (!data->scene)
		err_msg("Memory allocation failed\n", data);
	data->scene->north_texture = NULL;
	data->scene->west_texture = NULL;
	data->scene->east_texture = NULL;
	data->scene->floor_color[0] = 0;
	data->scene->floor_color[1] = 0;
	data->scene->floor_color[2] = 0;
	data->scene->ceiling_color[0] = 0;
	data->scene->ceiling_color[1] = 0;
	data->scene->ceiling_color[2] = 0;
	data->scene->map = NULL;
}

static void	set_player_dir_ns(t_data *data, char c)
{
	if (c == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.plane_x = 0.66;
		data->player.plane_y = 0;
	}
	else if (c == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.plane_x = -0.66;
		data->player.plane_y = 0;
	}
}

static void	set_player_dir_ew(t_data *data, char c)
{
	if (c == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = 0.66;
	}
	else if (c == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.plane_x = 0;
		data->player.plane_y = -0.66;
	}
}

void	init_player(t_data *data, int i, int j, char c)
{
	data->player.x = j + 0.5;
	data->player.y = i + 0.5;
	if (c == 'N' || c == 'S')
		set_player_dir_ns(data, c);
	else if (c == 'E' || c == 'W')
		set_player_dir_ew(data, c);
}
