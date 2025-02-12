/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:06:33 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/12 16:27:22 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (0);
	return (ft_strncmp(file + len - 4, ".cub", 4) == 0);
}

void	parsing(char *file, t_data *data)
{
	int	fd;

	(void)data;
	if (!check_extension(file))
		err_msg("Invalid file extension\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		err_msg("Cannot open file\n");
}
