/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 14:03:51 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/18 14:15:26 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall(t_data *data, t_ray *ray, int x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;

	step = ((double)ray->texture->height / ray->line_height);
	tex_pos = (ray->draw_start - data->image.height / 2 + ray->line_height / 2)
		* step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (ray->texture->height - 1);
		tex_pos += step;
		*(unsigned int *)(data->image.img_data + (y * data->image.size_line + x
					* (data->image.bpp
						/ 8))) = *(unsigned int *)(ray->texture->img_data
				+ (tex_y * ray->texture->size_line + ray->tex_x
					* (ray->texture->bpp / 8)));
		y++;
	}
}

void	draw_ceiling(t_data *data)
{
	int	x;
	int	y;
	int	color;

	color = (data->scene->ceiling_color[0] << 16) | (data->scene->ceiling_color[1] << 8) | data->scene->ceiling_color[2];
	y = 0;
	while (y < data->image.height / 2)
	{
		x = 0;
		while (x < data->image.width)
		{
			*(unsigned int *)(data->image.img_data + (y * data->image.size_line
						+ x * (data->image.bpp / 8))) = color;
			x++;
		}
		y++;
	}
}

void	draw_floor(t_data *data)
{
	int	x;
	int	y;
	int	color;

	color = (data->scene->floor_color[0] << 16) | (data->scene->floor_color[1] << 8) | data->scene->floor_color[2];
	y = data->image.height / 2;
	while (y < data->image.height)
	{
		x = 0;
		while (x < data->image.width)
		{
			*(unsigned int *)(data->image.img_data + (y * data->image.size_line
						+ x * (data->image.bpp / 8))) = color;
			x++;
		}
		y++;
	}
}
