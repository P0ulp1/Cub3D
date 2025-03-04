/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:42:31 by alibabab          #+#    #+#             */
/*   Updated: 2025/03/04 17:35:13 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	setup_hooks(t_data *data)
{
	mlx_hook(data->win, 17, 0, close_game, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_handler, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_hook(data->win, MotionNotify, PointerMotionMask, mouse_handler, data);
	mlx_mouse_hide(data->mlx, data->win);
	mlx_loop_hook(data->mlx, move_player, data);
}

double	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

int	update_south_texture(t_data *data)
{
	double	anim_speed;
	double	current_time;

	current_time = get_current_time();
	anim_speed = 0.2; // Change toutes les 200ms
	if (current_time - data->last_anim_update > anim_speed)
	{
		data->anim_frame++;
		if (data->anim_frame >= 4) // 4 frames d'animation
			data->anim_frame = 0;
		data->textures[SOUTH] = data->anim_textures[data->anim_frame];
		data->last_anim_update = current_time;
	}
	return (0);
}

void	render_scene(t_data *data)
{
	t_ray	ray;
	int		i;

	draw_ceiling(data);
	draw_floor(data);
	if (!ft_strcmp(data->scene->south_texture, "./textures/flam.xpm"))
		update_south_texture(data);
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
	// if (!ft_strcmp(data->scene->south_texture, "./textures/flam.xpm"))
	// 	mlx_loop_hook(data->mlx, update_south_texture, data);
	mlx_put_image_to_window(data->mlx, data->win, data->image.img, 0, 0);
	mlx_loop(data->mlx);
}
