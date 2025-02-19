/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:34:33 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/19 04:12:17 by alibabab         ###   ########.fr       */
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

static void	check_door(t_data *data, int x, int y)
{
	int	map_width;

	if (y < 0 || !data->scene->map[y])
		return ;
	map_width = (int)ft_strlen(data->scene->map[y]);
	if (x >= 0 && x < map_width && data->scene->map[y][x] == 'D')
		data->scene->map[y][x] = 'P';
}

void	open_door(t_data *data)
{
	int	x;
	int	y;
	int	range;

	data->door_open = 1;
	x = (int)data->player.x;
	y = (int)data->player.y;
	range = -2;
	while (range <= 2)
	{
		if (range != 0)
		{
			check_door(data, x + range, y);
			check_door(data, x, y + range);
		}
		range++;
	}
}
