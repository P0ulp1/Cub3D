/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_conversion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:07:12 by phautena          #+#    #+#             */
/*   Updated: 2024/11/18 15:04:58 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	p_conversion(void *ptr, int *count_ptr)
{
	uintptr_t	ptr_value;

	ptr_value = (uintptr_t)ptr;
	if (ptr_value == 0)
	{
		write(1, "(nil)", 5);
		*count_ptr += 5;
		return ;
	}
	write(1, "0x", 2);
	*count_ptr += 2;
	address_2_hex(ptr_value, count_ptr);
}

void	address_2_hex(size_t n, int *count_ptr)
{
	char	*table;

	table = "0123456789abcdef";
	if (n > 15)
	{
		address_2_hex(n / 16, count_ptr);
		address_2_hex(n % 16, count_ptr);
	}
	else
	{
		write(1, &table[n], 1);
		*count_ptr += 1;
	}
}
