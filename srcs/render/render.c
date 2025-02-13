/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:42:31 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/13 15:19:13 by alibabab         ###   ########.fr       */
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
	int	screen_w;
	int	screen_h;

	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		err_msg("Failed to initialize MLX\n", data);
	mlx_get_screen_size(data->mlx_ptr, &screen_w, &screen_h);
	data->win_ptr = mlx_new_window(data->mlx_ptr, screen_w, screen_h,
			"SUPER JEU DE OUF REGARDE C'EST OUF UN ECRAN NOIR");
	if (!data->win_ptr)
		err_msg("Failed to create window\n", data);
	mlx_hook(data->win_ptr, 17, 0, close_game, data);
	mlx_key_hook(data->win_ptr, key_handler, data);
	mlx_loop(data->mlx_ptr);
}

void	render(t_data *data)
{
	setup_window(data);
}
