/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:40:29 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/19 08:59:59 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (key == XK_space)
		open_door(data);
	if (key == XK_Left)
		data->player.rotate -= 1;
	if (key == XK_Right)
		data->player.rotate += 1;
	if (key == XK_Shift_L)
		data->move_speed = 0.009;
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == XK_w || key == XK_s)
		data->player.move_y = 0;
	if (key == XK_a || key == XK_d)
		data->player.move_x = 0;
	if (key == XK_Right || key == XK_Left)
		data->player.rotate = 0;
	if (key == XK_space)
		data->door_open = 0;
	if (key == XK_Shift_L)
		data->move_speed = 0.004;
	return (0);
}

int	mouse_handler(int x, int y, t_data *data)
{
	static int	old_x = 700 / 2;

	if (x > data->image.width - 20)
	{
		x = 20;
		mlx_mouse_move(data->mlx, data->win, x, y);
	}
	if (x < 20)
	{
		x = data->image.width - 20;
		mlx_mouse_move(data->mlx, data->win, x, y);
	}
	if (x == old_x)
		return (0);
	else if (x < old_x)
		rotate_player(data, -1);
	else if (x > old_x)
		rotate_player(data, 1);
	old_x = x;
	redraw_screen(data);
	return (0);
}
