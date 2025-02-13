/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:24:38 by phautena          #+#    #+#             */
/*   Updated: 2025/02/13 03:27:44 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>

# undef BUFFER_SIZE
# define BUFFER_SIZE 4096

typedef struct s_scene
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color[3];
	int		ceiling_color[3];
	char	**map;
}			t_scene;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_scene	*scene;
	// Player struct;
	// DDA struct;
}			t_data;

/// INIT
void		init_data(t_data *data);

/// PARSING
void		parsing(char *file, t_data *data);

void		check_character(t_data *data);
void		check_declarations(char **lines, t_data *data);
void		check_wall(char **map, t_data *data);

void		parse_map(char **lines, int start, t_data *data);
void		parse_textures(char *line, t_data *data);

/// FREE
void		err_msg(char *str, t_data *data);
void		free_data(t_data *data);

#endif
