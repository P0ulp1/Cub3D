/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_conversion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:50:44 by phautena          #+#    #+#             */
/*   Updated: 2024/06/06 12:08:45 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	s_conversion(char *string, int *count_ptr)
{
	int	i;

	if (string == NULL)
	{
		write(1, "(null)", 6);
		*count_ptr += 6;
		return ;
	}
	i = 0;
	while (string[i] != '\0')
		i++;
	write(1, string, i);
	*count_ptr += i;
}
