/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:24:38 by phautena          #+#    #+#             */
/*   Updated: 2025/01/30 13:44:11 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../get_next_line/get_next_line.h"
# include "../ft_printf/includes/ft_printf.h"
# include "../Libft/libft.h"

typedef struct	s_map
{
	char	*map_fil;
	char	**map;
	int		map_fd;
}				t_map;

typedef struct s_textures
{
	char	*NO_fil;
	char	*SO_fil;
	char	*WE_fil;
	char	*EA_fil;
	int		NO_fd;
	int		SO_fd;
	int		WE_fd;
	int		EA_fd;
}				t_textures;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		*map;
	t_textures	*textures;
	//Player struct
	//DDA struct
}				t_data;

#endif
