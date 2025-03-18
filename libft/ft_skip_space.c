/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alibabab <alibabab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:08:05 by alibabab          #+#    #+#             */
/*   Updated: 2025/03/18 14:08:15 by alibabab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_skip_space(char *str)
{
	if (!str)
		return (NULL);
	while (*str && ft_isspace(*str))
		str++;
	return (str);
}
