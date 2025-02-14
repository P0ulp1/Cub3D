/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:19:51 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/14 18:34:36 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_image *image, int x_start, int y_start, int width,
		int height, int color)
{
	int	x;
	int	y;
	int	pixel;

	y = y_start;
	while (y < y_start + height)
	{
		x = x_start;
		while (x < x_start + width)
		{
			if (x >= 0 && x < image->width && y >= 0 && y < image->height)
			{
				pixel = (y * image->size_line) + (x * (image->bpp / 8));
				*((unsigned int *)(image->img_data + pixel)) = color;
			}
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_data *data)
{
	int	map_x;
	int	map_y;
	int	color;

	map_y = 0;
	while (data->scene->map[map_y])
	{
		map_x = 0;
		while (data->scene->map[map_y][map_x] != '\0')
		{
			if (data->scene->map[map_y][map_x] == '1')
				color = WHITE;
			else
				color = BLACK;
			draw_square(&data->image, map_x * MINIMAP_SIZE + 10, map_y
				* MINIMAP_SIZE + 10, MINIMAP_SIZE, MINIMAP_SIZE, color);
			map_x++;
		}
		map_y++;
	}
	draw_square(&data->image, (int)data->player.x * MINIMAP_SIZE + 10,
		(int)data->player.y * MINIMAP_SIZE + 10, MINIMAP_SIZE, MINIMAP_SIZE,
		RED);
}
