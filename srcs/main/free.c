/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:17:40 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/19 07:34:26 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **lines)
{
	int	i;

	i = -1;
	while (lines[++i])
		free(lines[i]);
	free(lines);
}

void	free_scene(t_data *data)
{
	int	i;

	if (data->scene)
	{
		if (data->scene->north_texture)
			free(data->scene->north_texture);
		if (data->scene->south_texture)
			free(data->scene->south_texture);
		if (data->scene->west_texture)
			free(data->scene->west_texture);
		if (data->scene->east_texture)
			free(data->scene->east_texture);
		if (data->scene->door_texture)
			free(data->scene->door_texture);
		if (data->scene->map)
		{
			i = -1;
			while (data->scene->map[++i])
				free(data->scene->map[i]);
			free(data->scene->map);
		}
		free(data->scene);
	}
}

static void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (data->textures[i])
		{
			mlx_destroy_image(data->mlx, data->textures[i]->img);
			free(data->textures[i]);
		}
		i++;
	}
}

void	free_data(t_data *data)
{
	free_scene(data);
	free_textures(data);
	if (data->image.img)
	{
		mlx_destroy_image(data->mlx, data->image.img);
		data->image.img = NULL;
	}
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}
