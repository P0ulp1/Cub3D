/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_conversion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:14:06 by phautena          #+#    #+#             */
/*   Updated: 2024/11/18 15:04:41 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	u_conversion(unsigned int n, int *count_ptr)
{
	int	n2c;

	if (n > 9)
	{
		u_conversion(n / 10, count_ptr);
		u_conversion(n % 10, count_ptr);
	}
	else
	{
		n2c = n + '0';
		write(1, &n2c, 1);
		*count_ptr += 1;
	}
}
