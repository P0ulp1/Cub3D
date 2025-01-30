/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   di_conversion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:13:17 by phautena          #+#    #+#             */
/*   Updated: 2024/06/06 12:08:07 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_int_min(int *count_ptr)
{
	write(1, "-2147483648", 11);
	*count_ptr += 11;
	return ;
}

void	di_conversion(int n, int *count_ptr)
{
	int	n2c;

	if (n == INT_MIN)
	{
		print_int_min(count_ptr);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		*count_ptr += 1;
		n *= -1;
		di_conversion(n, count_ptr);
	}
	else if (n > 9)
	{
		di_conversion(n / 10, count_ptr);
		di_conversion(n % 10, count_ptr);
	}
	else
	{
		n2c = n + '0';
		write(1, &n2c, 1);
		*count_ptr += 1;
	}
}
