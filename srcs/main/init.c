/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 03:23:57 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/13 03:29:45 by alibabab         ###   ########.fr       */
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
