/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_isspace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:26:52 by alibabab          #+#    #+#             */
/*   Updated: 2025/02/12 20:27:45 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_isspace(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}
