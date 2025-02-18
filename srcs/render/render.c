/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:42:31 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/18 13:43:30 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		err_msg("Failed to initialize MLX\n", data);
	mlx_get_screen_size(data->mlx, &data->image.width, &data->image.height);
	data->image.width = 720;
	data->image.height = 480;
	data->win = mlx_new_window(data->mlx, data->image.width, data->image.height,
			"SUPER JEU DE FOU");
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
}

static void	setup_hooks(t_data *data)
{
	mlx_hook(data->win, 17, 0, close_game, data);
	mlx_hook(data->win, KeyPress, KeyPressMask, key_handler, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, key_release, data);
	mlx_loop_hook(data->mlx, move_player, data);
}

static void	init_ray(t_data *data, t_ray *ray, int i)
{
	ray->camera_x = 2 * i / (double)data->image.width - 1;
	ray->dir_x = data->player.dir_x + data->player.plane_x * ray->camera_x;
	ray->dir_y = data->player.dir_y + data->player.plane_y * ray->camera_x;
	ray->map_x = (int)data->player.x;
	ray->map_y = (int)data->player.y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
}

static void	calculate_step(t_data *data, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (data->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - data->player.x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (data->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - data->player.y)
			* ray->delta_dist_y;
	}
}

static void	perform_dda(t_data *data, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->scene->map[ray->map_y][ray->map_x] == '1'
			|| data->scene->map[ray->map_y][ray->map_x] == 'D')
			ray->hit = 1;
	}
}

static void	calculate_wall(t_data *data, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(data->image.height / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + data->image.height / 2;
	ray->draw_end = ray->line_height / 2 + data->image.height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= data->image.height)
		ray->draw_end = data->image.height - 1;
	if (data->scene->map[ray->map_y][ray->map_x] == 'D')
		ray->texture = data->textures[DOOR];
	else if (ray->side == 0)
	{
		if (ray->step_x > 0)
			ray->texture = data->textures[EAST];
		else
			ray->texture = data->textures[WEST];
	}
	else
	{
		if (ray->step_y > 0)
			ray->texture = data->textures[SOUTH];
		else
			ray->texture = data->textures[NORTH];
	}
	if (ray->side == 0)
		wall_x = data->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = data->player.x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	ray->tex_x = (int)(wall_x * ray->texture->width);
}

static void	draw_wall(t_data *data, t_ray *ray, int x)
{
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;
	char	*src;
	char	*dst;

	step = (double)ray->texture->height / ray->line_height;
	tex_pos = (ray->draw_start - data->image.height / 2 + ray->line_height / 2)
		* step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (ray->texture->height - 1);
		tex_pos += step;
		src = ray->texture->img_data + (tex_y * ray->texture->size_line
				+ ray->tex_x * (ray->texture->bpp / 8));
		dst = data->image.img_data + (y * data->image.size_line + x
				* (data->image.bpp / 8));
		*(unsigned int *)dst = *(unsigned int *)src;
		y++;
	}
}

void	draw_ceiling(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->image.height / 2)
	{
		x = 0;
		while (x < data->image.width)
		{
			*(unsigned int *)(data->image.img_data + (y * data->image.size_line
						+ x * (data->image.bpp
							/ 8))) = (data->scene->ceiling_color[0] << 16) | (data->scene->ceiling_color[1] << 8) | data->scene->ceiling_color[2];
			x++;
		}
		y++;
	}
}

void	draw_floor(t_data *data)
{
	int	x;
	int	y;

	y = data->image.height / 2;
	while (y < data->image.height)
	{
		x = 0;
		while (x < data->image.width)
		{
			*(unsigned int *)(data->image.img_data + (y * data->image.size_line
						+ x * (data->image.bpp
							/ 8))) = (data->scene->floor_color[0] << 16) | (data->scene->floor_color[1] << 8) | data->scene->floor_color[2];
			x++;
		}
		y++;
	}
}

void	render_scene(t_data *data)
{
	t_ray	ray;
	int		i;

	draw_ceiling(data);
	draw_floor(data);
	i = 0;
	while (i < data->image.width)
	{
		init_ray(data, &ray, i);
		calculate_step(data, &ray);
		perform_dda(data, &ray);
		calculate_wall(data, &ray);
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
