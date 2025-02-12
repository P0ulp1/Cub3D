/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:24:38 by phautena          #+#    #+#             */
/*   Updated: 2025/02/12 16:25:49 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_map
{
	char		*map_fil;
	char		**map;
	int			map_fd;
}				t_map;

typedef struct s_textures
{
	char		*NO_fil;
	char		*SO_fil;
	char		*WE_fil;
	char		*EA_fil;
	int			NO_fd;
	int			SO_fd;
	int			WE_fd;
	int			EA_fd;
	// FLOOR RGB value;
	// CEILING RGB value;
}				t_textures;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		*map;
	t_textures	*textures;
	// Player struct;
	// DDA struct;
}				t_data;

/// PARSING
void			parsing(char *file, t_data *data);

/// FREE
void			err_msg(char *str);

#endif
