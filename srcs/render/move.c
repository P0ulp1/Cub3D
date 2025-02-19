/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 22:16:36 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/19 04:14:56 by alibabab         ###   ########.fr       */
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

static int	rotate_player(t_data *data, double direction)
{
	t_player	*p;
	double		tmp_x;
	double		rotspeed;

	p = &data->player;
	rotspeed = data->rot_speed * direction;
	tmp_x = p->dir_x;
	p->dir_x = p->dir_x * cos(rotspeed) - p->dir_y * sin(rotspeed);
	p->dir_y = tmp_x * sin(rotspeed) + p->dir_y * cos(rotspeed);
	tmp_x = p->plane_x;
	p->plane_x = p->plane_x * cos(rotspeed) - p->plane_y * sin(rotspeed);
	p->plane_y = tmp_x * sin(rotspeed) + p->plane_y * cos(rotspeed);
	return (1);
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
	if (data->player.rotate == 1)
		moved += rotate_player(data, 1);
	if (data->player.rotate == -1)
		moved += rotate_player(data, -1);
	if (data->door_open == 1)
		moved += 1;
	if (moved && data->win && data->mlx)
	{
		close_door(data);
		render_scene(data);
		draw_minimap(data);
		mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	}
	return (moved);
}
