/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:47:49 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/18 13:02:16 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_scene(t_data *data)
{
	data->scene = malloc(sizeof(t_scene));
	if (!data->scene)
		err_msg("Memory allocation failed\n", data);
	data->scene->north_texture = NULL;
	data->scene->south_texture = NULL;
	data->scene->west_texture = NULL;
	data->scene->east_texture = NULL;
	data->scene->door_texture = NULL;
	data->scene->floor_color[0] = 0;
	data->scene->floor_color[1] = 0;
	data->scene->floor_color[2] = 0;
	data->scene->ceiling_color[0] = 0;
	data->scene->ceiling_color[1] = 0;
	data->scene->ceiling_color[2] = 0;
	data->scene->map = NULL;
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->scene = NULL;
	data->textures[NORTH] = NULL;
	data->textures[SOUTH] = NULL;
	data->textures[WEST] = NULL;
	data->textures[EAST] = NULL;
	data->textures[DOOR] = NULL;
	data->has_door = 0;
	data->image.img = NULL;
	data->image.img_data = NULL;
	data->image.width = 0;
	data->image.height = 0;
	data->image.bpp = 0;
	data->image.size_line = 0;
	data->image.endian = 0;
	init_scene(data);
}
