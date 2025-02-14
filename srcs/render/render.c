/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:42:31 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/14 22:54:57 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		err_msg("Failed to initialize MLX\n", data);
	mlx_get_screen_size(data->mlx, &data->image.width, &data->image.height);
	data->win = mlx_new_window(data->mlx, data->image.width, data->image.height,
			"SUPER JEU DE OUF");
	if (!data->win)
		err_msg("Failed to create window\n", data);
}

static void	init_image(t_data *data)
{
	data->image.img = mlx_new_image(data->mlx, data->image.width,
			data->image.height);
	if (!data->image.img)
		err_msg("Failed to create image\n", data);
	data->image.img_data = mlx_get_data_addr(data->image.img, &data->image.bpp,
			&data->image.size_line, &data->image.endian);
	if (!data->image.img_data)
		err_msg("Failed to get image data address\n", data);
	draw_minimap(data);
}

static void	setup_hooks(t_data *data)
{
	mlx_hook(data->win, 17, 0, close_game, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_handler, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_loop_hook(data->mlx, move_player, data);
}

void	render(t_data *data)
{
	init_window(data);
	init_image(data);
	setup_hooks(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	mlx_loop(data->mlx);
}
