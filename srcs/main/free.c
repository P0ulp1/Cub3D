/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:17:40 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/13 15:54:27 by alibabab         ###   ########.fr       */
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

	i = 0;
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
		if (data->scene->map)
		{
			while (data->scene->map[i])
			{
				free(data->scene->map[i]);
				i++;
			}
			free(data->scene->map);
		}
		free(data->scene);
	}
}

void	free_data(t_data *data)
{
	free_scene(data);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
}
