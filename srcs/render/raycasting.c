/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:56:34 by alibabab          #+#    #+#             */
/*   Updated: 2025/03/04 18:46:54 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_data *data, t_ray *ray, int i)
{
	ray->camera_x = 2 * i / (double)data->image.width - 1;
	ray->dir_x = data->player.dir_x + data->player.plane_x * ray->camera_x;
	ray->dir_y = data->player.dir_y + data->player.plane_y * ray->camera_x;
	ray->map_x = (int)data->player.x;
	ray->map_y = (int)data->player.y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
}

void	calculate_step(t_data *data, t_ray *ray)
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

void	perform_dda(t_data *data, t_ray *ray)
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

void	calculate_wall_distances(t_data *data, t_ray *ray)
{
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
}

void	select_wall_texture(t_data *data, t_ray *ray)
{
	double	wall_x;

	if (data->scene->map[ray->map_y][ray->map_x] == 'D')
		ray->texture = data->textures[DOOR];
	else if (ray->side == 0)
	{
		if (ray->step_x > 0)
			ray->texture = data->textures[EAST];
		else
			ray->texture = data->textures[WEST];
	}
	else if (ray->step_y > 0 && data->has_animation)
		ray->texture = data->anim_textures[data->anim_frame];
	else if (ray->step_y > 0)
		ray->texture = data->textures[SOUTH];
	else
		ray->texture = data->textures[NORTH];
	if (ray->side == 0)
		wall_x = data->player.y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = data->player.x + ray->perp_wall_dist * ray->dir_x;
	ray->tex_x = (int)((wall_x - floor(wall_x)) * ray->texture->width);
}
