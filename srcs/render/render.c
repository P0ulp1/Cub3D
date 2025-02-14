/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:42:31 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/14 18:20:18 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_handler(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_game(data);
	return (0);
}

void	setup_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		err_msg("Failed to initialize MLX\n", data);
	mlx_get_screen_size(data->mlx_ptr, &data->image.width, &data->image.height);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->image.width,
			data->image.height, "SUPER JEU DE OUF");
	if (!data->win_ptr)
		err_msg("Failed to create window\n", data);
	data->image.img = mlx_new_image(data->mlx_ptr, data->image.width,
			data->image.height);
	if (!data->image.img)
		err_msg("Failed to create image\n", data);
	data->image.img_data = mlx_get_data_addr(data->image.img, &data->image.bpp,
			&data->image.size_line, &data->image.endian);
	if (!data->image.img_data)
		err_msg("Failed to get image data address\n", data);
	mlx_hook(data->win_ptr, 17, 0, close_game, data);
	mlx_key_hook(data->win_ptr, key_handler, data);
}

void	render(t_data *data)
{
	setup_window(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->image.img, 0,
		0);
	mlx_destroy_image(data->mlx_ptr, data->image.img);
	mlx_loop(data->mlx_ptr);
}