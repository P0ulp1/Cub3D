/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibaba <alibaba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:24:38 by phautena          #+#    #+#             */
/*   Updated: 2025/03/06 12:25:30 by alibaba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>

# undef BUFFER_SIZE
# define BUFFER_SIZE 4096

# define MS 8 // minimap square size

# define WIDTH 1920
# define HEIGHT 1080

# define MOVSPEED 0.04
# define ROTSPEED 0.03

# define ANIMSPEED 5

/// COLORS

# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define DOOR 4

typedef struct s_scene
{
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	char		*door_texture;
	int			floor_color[3];
	int			ceiling_color[3];
	char		**map;
	int			map_width;
	int			map_height;
}				t_scene;

typedef struct s_player
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	double		move_x;
	double		move_y;
	double		rotate;
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

typedef struct s_ray
{
	double		camera_x;
	double		dir_x;
	double		dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	t_image		*texture;
	int			tex_x;
}				t_ray;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_scene		*scene;
	t_player	player;
	t_image		image;
	t_image		*textures[5];
	t_image		*anim_textures[6];
	int			has_door;
	int			door_open;
	double		move_speed;
	double		rot_speed;
	int			mouse;
	int			anim_frame;
	int			has_animation;
}				t_data;

typedef struct s_minimap
{
	int			x;
	int			y;
	int			width;
	int			height;
}				t_minimap;

/// INIT

void			init_data(t_data *data);
void			init_player(t_data *data, int i, int j, char c);
void			init_textures(t_data *data);
void			init_image(t_data *data);
void			init_window(t_data *data);

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
void			check_textures_exist(t_data *data);

void			parse_map(char **lines, int start, t_data *data);
void			parse_textures(char *line, t_data *data, char **to_free);

/// RENDER

void			render(t_data *data);
void			render_scene(t_data *data);

/// RAYCASTING

void			calculate_wall_distances(t_data *data, t_ray *ray);
void			select_wall_texture(t_data *data, t_ray *ray);
void			perform_dda(t_data *data, t_ray *ray);
void			calculate_step(t_data *data, t_ray *ray);
void			init_ray(t_data *data, t_ray *ray, int i);

/// DRAW

void			draw_wall(t_data *data, t_ray *ray, int x);
void			draw_ceiling(t_data *data);
void			draw_floor(t_data *data);

/// BONUS

void			draw_minimap(t_data *data);
void			open_door(t_data *data);
void			close_door(t_data *data);
int				mouse_handler(int x, int y, t_data *data);

/// MOVE

int				key_handler(int key, t_data *data);
int				key_release(int key, t_data *data);
int				move_player(t_data *data);
int				rotate_player(t_data *data, double direction);

void			redraw_screen(t_data *data);

#endif
