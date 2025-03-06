/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:47:49 by alibabab          #+#    #+#             */
/*   Updated: 2025/03/06 12:25:27 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_scene(t_data *data)
{
	data->scene = NULL;
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

static void	init_null_textures(t_data *data)
{
	data->textures[NORTH] = NULL;
	data->textures[SOUTH] = NULL;
	data->textures[WEST] = NULL;
	data->textures[EAST] = NULL;
	data->textures[DOOR] = NULL;
	data->anim_textures[0] = NULL;
	data->anim_textures[1] = NULL;
	data->anim_textures[2] = NULL;
	data->anim_textures[3] = NULL;
	data->anim_textures[4] = NULL;
	data->anim_textures[5] = NULL;
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->has_door = 0;
	data->door_open = 0;
	data->move_speed = 0;
	data->rot_speed = 0;
	data->image.img = NULL;
	data->image.img_data = NULL;
	data->image.width = 0;
	data->image.height = 0;
	data->image.bpp = 0;
	data->image.size_line = 0;
	data->image.endian = 0;
	data->anim_frame = 0;
	data->has_animation = 0;
	init_null_textures(data);
	init_scene(data);
}
