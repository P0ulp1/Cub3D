/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_summary.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:43:18 by phautena          #+#    #+#             */
/*   Updated: 2024/06/10 14:17:22 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	function_summary(char c, va_list args, int *i_ptr, int *count_ptr)
{
	if (c == 'c')
		c_conversion(va_arg(args, int), count_ptr);
	else if (c == 'd' || c == 'i')
		di_conversion(va_arg(args, int), count_ptr);
	else if (c == 'X')
		x_upper_conversion(va_arg(args, unsigned int), count_ptr);
	else if (c == 'x')
		x_conversion(va_arg(args, unsigned int), count_ptr);
	else if (c == 's')
		s_conversion(va_arg(args, char *), count_ptr);
	else if (c == 'p')
		p_conversion(va_arg(args, void *), count_ptr);
	else if (c == 'u')
		u_conversion(va_arg(args, unsigned int), count_ptr);
	else
	{
		write(1, "%", 1);
		count_ptr += 1;
	}
	*i_ptr += 2;
}
