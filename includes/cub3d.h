/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:24:38 by phautena          #+#    #+#             */
/*   Updated: 2025/02/13 16:59:50 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <stdio.h>

# undef BUFFER_SIZE
# define BUFFER_SIZE 4096

// # define SCREEN_WIDTH 1920
// # define SCREEN_HEIGHT 1080

typedef struct s_scene
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	int			floor_color[3];
	int			ceiling_color[3];
	char		**map;
}				t_scene;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_speed;
	double		rot_speed;
}				t_player;

typedef struct s_image
{
	void		*img;
	char		*img_data;
	int			bpp;
	int			size_line;
	int			endian;
	int			width;
	int			height;
}				t_image;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_scene		*scene;
	t_player	player;
	t_image		image;
	// DDA struct;
}				t_data;

/// INIT
void			init_data(t_data *data);
void			init_player(t_data *data, int i, int j, char c);

/// EXIT
void			err_msg(char *str, t_data *data);
int				close_game(t_data *data);

/// FREE
void			free_data(t_data *data);
void			free_split(char **lines);

/// PARSING
void			parsing(char *file, t_data *data);

void			check_character(t_data *data);
void			check_declarations(char **lines, t_data *data);
void			check_wall(char **map, t_data *data);
void			check_textures_files(t_data *data);

void			parse_map(char **lines, int start, t_data *data);
void			parse_textures(char *line, t_data *data, char **to_free);

/// RENDER
void			render(t_data *data);

#endif
