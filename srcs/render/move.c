/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:16:36 by alibabab          #+#    #+#             */
/*   Updated: 2025/03/05 12:37:38 by alibabab         ###   ########.fr       */
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

static int	move_player_position(t_data *data, char mode, double new_x,
		double new_y)
{
	if (mode == 'L')
	{
		new_x = data->player.x + data->player.dir_y * data->move_speed;
		new_y = data->player.y - data->player.dir_x * data->move_speed;
	}
	else if (mode == 'R')
	{
		new_x = data->player.x - data->player.dir_y * data->move_speed;
		new_y = data->player.y + data->player.dir_x * data->move_speed;
	}
	else if (mode == 'B')
	{
		new_x = data->player.x - data->player.dir_x * data->move_speed;
		new_y = data->player.y - data->player.dir_y * data->move_speed;
	}
	else if (mode == 'F')
	{
		new_x = data->player.x + data->player.dir_x * data->move_speed;
		new_y = data->player.y + data->player.dir_y * data->move_speed;
	}
	return (valid_move(data, new_x, new_y));
}

int	rotate_player(t_data *data, double direction)
{
	double	rotspeed;
	double	tmp_x;

	rotspeed = data->rot_speed * direction;
	tmp_x = data->player.dir_x;
	data->player.dir_x = data->player.dir_x * cos(rotspeed) - data->player.dir_y
		* sin(rotspeed);
	data->player.dir_y = tmp_x * sin(rotspeed) + data->player.dir_y
		* cos(rotspeed);
	tmp_x = data->player.plane_x;
	data->player.plane_x = data->player.plane_x * cos(rotspeed)
		- data->player.plane_y * sin(rotspeed);
	data->player.plane_y = tmp_x * sin(rotspeed) + data->player.plane_y
		* cos(rotspeed);
	return (1);
}

void	redraw_screen(t_data *data)
{
	close_door(data);
	render_scene(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
}

int	move_player(t_data *data)
{
	int		moved;
	double	new_x;
	double	new_y;

	new_x = 0;
	new_y = 0;
	moved = 0;
	if (data->player.move_y == 1)
		moved += move_player_position(data, 'F', new_x, new_y);
	if (data->player.move_y == -1)
		moved += move_player_position(data, 'B', new_x, new_y);
	if (data->player.move_x == -1)
		moved += move_player_position(data, 'L', new_x, new_y);
	if (data->player.move_x == 1)
		moved += move_player_position(data, 'R', new_x, new_y);
	if (data->player.rotate == 1)
		moved += rotate_player(data, 1);
	if (data->player.rotate == -1)
		moved += rotate_player(data, -1);
	if (data->door_open == 1)
		moved += 1;
	if (moved || data->has_animation == 1)
		redraw_screen(data);
	return (moved);
}
