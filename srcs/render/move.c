/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:16:36 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/14 22:17:51 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	valid_move(t_data *data, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (data->scene->map[(int)data->player.y][(int)new_x] != '1'
		&& data->scene->map[(int)data->player.y][(int)new_x] != 'D')
	{
		data->player.x = new_x;
		moved = 1;
	}
	if (data->scene->map[(int)new_y][(int)data->player.x] != '1'
		&& data->scene->map[(int)new_y][(int)data->player.x] != 'D')
	{
		data->player.y = new_y;
		moved = 1;
	}
	return (moved);
}

static int	move_player_position(t_data *data, char mode)
{
	double	new_x;
	double	new_y;

	if (mode == 'L')
	{
		new_x = data->player.x + data->player.dir_y * MOVESPEED;
		new_y = data->player.y - data->player.dir_x * MOVESPEED;
	}
	else if (mode == 'R')
	{
		new_x = data->player.x - data->player.dir_y * MOVESPEED;
		new_y = data->player.y + data->player.dir_x * MOVESPEED;
	}
	else if (mode == 'B')
	{
		new_x = data->player.x - data->player.dir_x * MOVESPEED;
		new_y = data->player.y - data->player.dir_y * MOVESPEED;
	}
	else if (mode == 'F')
	{
		new_x = data->player.x + data->player.dir_x * MOVESPEED;
		new_y = data->player.y + data->player.dir_y * MOVESPEED;
	}
	return (valid_move(data, new_x, new_y));
}

int	move_player(t_data *data)
{
	int	moved;

	moved = 0;
	if (data->player.move_y == 1)
		moved += move_player_position(data, 'F');
	if (data->player.move_y == -1)
		moved += move_player_position(data, 'B');
	if (data->player.move_x == -1)
		moved += move_player_position(data, 'L');
	if (data->player.move_x == 1)
		moved += move_player_position(data, 'R');
	if (moved && data->win_ptr && data->mlx_ptr)
	{
		draw_minimap(data);
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image.img,
			0, 0);
	}
	return (moved);
}

int	key_handler(int key, t_data *data)
{
	if (key == XK_Escape)
		close_game(data);
	if (key == XK_w)
		data->player.move_y = 1;
	if (key == XK_a)
		data->player.move_x = -1;
	if (key == XK_s)
		data->player.move_y = -1;
	if (key == XK_d)
		data->player.move_x = 1;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == XK_w || key == XK_s)
		data->player.move_y = 0;
	if (key == XK_a || key == XK_d)
		data->player.move_x = 0;
	return (0);
}
