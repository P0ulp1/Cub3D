/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:42:31 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/13 15:07:28 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_window(t_data *data)
{
	int	screen_w;
	int	screen_h;

	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		err_msg("Failed to initialize MLX\n", data);
	mlx_get_screen_size(data->mlx_ptr, &screen_w, &screen_h);
	data->win_ptr = mlx_new_window(data->mlx_ptr, screen_w, screen_h,
			"SUPER JEUX DE OUF");
	if (!data->win_ptr)
		err_msg("Failed to create window\n", data);
	mlx_loop(data->mlx_ptr);
}

void	render(t_data *data)
{
	setup_window(data);
}