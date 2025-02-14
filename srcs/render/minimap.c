/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:19:51 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/14 18:50:31 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_square(t_image *image, t_minimap *mini, int color)
{
	int	x;
	int	y;
	int	pixel;

	y = mini->y;
	while (y < mini->y + mini->height)
	{
		x = mini->x;
		while (x < mini->x + mini->width)
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
	int			map_x;
	int			map_y;
	int			color;
	t_minimap	mini;

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
			mini = (t_minimap){.x = map_x * MS + 10, .y = map_y * MS + 10,
				.width = MS, .height = MS};
			draw_square(&data->image, &mini, color);
			map_x++;
		}
		map_y++;
	}
	mini = (t_minimap){.x = (int)data->player.x * MS + 10,
		.y = (int)data->player.y * MS + 10, .width = MS, .height = MS};
	draw_square(&data->image, &mini, RED);
}
