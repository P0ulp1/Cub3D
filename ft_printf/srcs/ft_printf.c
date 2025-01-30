/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:32:25 by phautena          #+#    #+#             */
/*   Updated: 2024/06/10 14:24:18 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		*i_ptr;
	int		count;
	int		*count_ptr;

	init_var(&i, &count);
	i_ptr = &i;
	count_ptr = &count;
	if (format == NULL)
		return (-1);
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] != '%')
			print_char(i_ptr, format[i], count_ptr);
		else if (format[i] == '%' && format[i + 1] == '%')
			print_percent(i_ptr, count_ptr);
		else if (format[i] == '%' && format[i + 1] == '\0')
			return (-1);
		else if (format[i] == '%')
			function_summary(format[i + 1], args, i_ptr, count_ptr);
	}
	va_end(args);
	return (count);
}

void	init_var(int *i, int *count)
{
	*i = 0;
	*count = 0;
}
