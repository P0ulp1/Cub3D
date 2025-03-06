/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:42:31 by alibabab          #+#    #+#             */
/*   Updated: 2025/03/06 10:11:34 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_hooks(t_data *data)
{
	mlx_hook(data->win, 17, 0, close_game, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_handler, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->win, MotionNotify, PointerMotionMask, mouse_handler, data);
	// mlx_mouse_hide(data->mlx, data->win);
	mlx_loop_hook(data->mlx, move_player, data);
}

static void	update_animation(t_data *data)
{
	static int	frame_count = 0;

	frame_count++;
	if (frame_count >= ANIMSPEED)
	{
		frame_count = 0;
		data->anim_frame = (data->anim_frame + 1) % 6;
	}
}

void	render_scene(t_data *data)
{
	t_ray	ray;
	int		i;

	draw_ceiling(data);
	draw_floor(data);
	if (data->has_animation == 1)
		update_animation(data);
	i = 0;
	while (i < data->image.width)
	{
		init_ray(data, &ray, i);
		calculate_step(data, &ray);
		perform_dda(data, &ray);
		calculate_wall_distances(data, &ray);
		select_wall_texture(data, &ray);
		draw_wall(data, &ray, i);
		i++;
	}
}

void	render(t_data *data)
{
	init_window(data);
	init_textures(data);
	init_image(data);
	render_scene(data);
	draw_minimap(data);
	setup_hooks(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	mlx_loop(data->mlx);
}
