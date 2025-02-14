/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:34:33 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/14 22:35:46 by alibabab         ###   ########.fr       */
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
				if (!((player_x - x <= 1 && player_x - x >= -1 && player_y == y)
						|| (player_y - y <= 1 && player_y - y >= -1
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

	x = (int)data->player.x;
	y = (int)data->player.y;
	if (data->scene->map[y][x + 1] == 'D')
		data->scene->map[y][x + 1] = 'P';
	else if (data->scene->map[y][x - 1] == 'D')
		data->scene->map[y][x - 1] = 'P';
	else if (data->scene->map[y + 1][x] == 'D')
		data->scene->map[y + 1][x] = 'P';
	else if (data->scene->map[y - 1][x] == 'D')
		data->scene->map[y - 1][x] = 'P';
}
