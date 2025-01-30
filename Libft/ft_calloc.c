/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:46:11 by phautena          #+#    #+#             */
/*   Updated: 2024/11/18 15:03:39 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*memo;
	size_t			i;

	if (nmemb < 1 || size < 1)
	{
		memo = NULL;
		return (memo);
	}
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	memo = malloc(nmemb * size);
	if (memo == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		memo[i] = 0;
		i++;
	}
	return (memo);
}
