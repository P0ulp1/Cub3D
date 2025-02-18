/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:34:33 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/18 13:46:54 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	close_door(t_data *data)
{
	int	x;
	int	y;
	int	player_x;
	int	player_y;

	player_x = (int)data->player.x;
	player_y = (int)data->player.y;
	y = 0;
	while (data->scene->map[y])
	{
		x = 0;
		while (data->scene->map[y][x])
		{
			if (data->scene->map[y][x] == 'P')
			{
				if (!((player_x - x <= 2 && player_x - x >= -2 && player_y == y)
						|| (player_y - y <= 2 && player_y - y >= -2
							&& player_x == x)))
					data->scene->map[y][x] = 'D';
			}
			x++;
		}
		y++;
	}
}

void	open_door(t_data *data)
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	map_height;
	int	map_width;

	x = (int)data->player.x;
	y = (int)data->player.y;
	map_height = 0;
	while (data->scene->map[map_height])
		map_height++;
	dx = -2;
	while (dx <= 2)
	{
		if (dx != 0)
		{
			map_width = (int)ft_strlen(data->scene->map[y]);
			if (x + dx >= 0 && x + dx < map_width && data->scene->map[y][x
				+ dx] == 'D')
				data->scene->map[y][x + dx] = 'P';
		}
		dx += 1;
	}
	dy = -2;
	while (dy <= 2)
	{
		if (dy != 0)
		{
			if (y + dy >= 0 && y + dy < map_height)
			{
				map_width = (int)ft_strlen(data->scene->map[y + dy]);
				if (x < map_width && data->scene->map[y + dy][x] == 'D')
					data->scene->map[y + dy][x] = 'P';
			}
		}
		dy += 1;
	}
}
