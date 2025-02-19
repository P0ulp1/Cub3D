/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:40:29 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/19 04:14:26 by alibabab         ###   ########.fr       */
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
	return (0);
}
