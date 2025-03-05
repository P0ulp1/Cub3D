/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:02:23 by alibabab          #+#    #+#             */
/*   Updated: 2025/03/05 12:31:30 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_image	*load_texture(t_data *data, char *path)
{
	t_image	*texture;

	texture = malloc(sizeof(t_image));
	if (!texture)
		err_msg("Failed to allocate memory for texture\n", data);
	texture->img = mlx_xpm_file_to_image(data->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
		err_msg("Failed to load texture\n", data);
	texture->img_data = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->size_line, &texture->endian);
	if (!texture->img_data)
		err_msg("Failed to get texture data address\n", data);
	return (texture);
}

void	init_anim_textures(t_data *data)
{
	data->anim_textures[0] = load_texture(data, "./textures/flam.xpm");
	data->anim_textures[1] = load_texture(data, "./textures/south_1.xpm");
	data->anim_textures[2] = load_texture(data, "./textures/south_2.xpm");
	data->anim_textures[3] = load_texture(data, "./textures/south_3.xpm");
	data->anim_textures[4] = load_texture(data, "./textures/south_4.xpm");
	data->anim_textures[5] = load_texture(data, "./textures/south_5.xpm");
	data->has_animation = 1;
	if (!data->anim_textures[0] || !data->anim_textures[1]
		|| !data->anim_textures[2] || !data->anim_textures[3]
		|| !data->anim_textures[4] || !data->anim_textures[5])
		err_msg("Failed to load textures\n", data);
}

void	init_textures(t_data *data)
{
	data->textures[NORTH] = load_texture(data, data->scene->north_texture);
	data->textures[SOUTH] = load_texture(data, data->scene->south_texture);
	data->textures[EAST] = load_texture(data, data->scene->east_texture);
	data->textures[WEST] = load_texture(data, data->scene->west_texture);
	if (data->scene->door_texture)
	{
		data->textures[DOOR] = load_texture(data, data->scene->door_texture);
		if (!data->textures[DOOR])
			err_msg("Failed to load door texture\n", data);
	}
	if (!data->textures[NORTH] || !data->textures[SOUTH]
		|| !data->textures[EAST] || !data->textures[WEST])
		err_msg("Failed to load textures\n", data);
	if (!ft_strcmp(data->scene->south_texture, "./textures/flam.xpm"))
		init_anim_textures(data);
}

void	init_window(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		err_msg("Failed to initialize MLX\n", data);
	mlx_get_screen_size(data->mlx, &data->image.width, &data->image.height);
	data->image.width = 1920;
	data->image.height = 1080;
	/// A MODIFIER
	data->move_speed = 0.04;
	data->rot_speed = 0.03;
	// data->move_speed = 0.03 * (data->image.width / 800.0);
	// data->rot_speed = 0.06 * (data->image.width / 800.0);
	data->win = mlx_new_window(data->mlx, data->image.width, data->image.height,
			"SUPER JEU DE FOU");
	if (!data->win)
		err_msg("Failed to create window\n", data);
}

void	init_image(t_data *data)
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
