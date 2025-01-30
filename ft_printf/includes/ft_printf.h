/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:34:21 by phautena          #+#    #+#             */
/*   Updated: 2024/06/10 14:19:35 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <limits.h>
# include <stdio.h>

int		ft_printf(const char *format, ...);
void	c_conversion(int character, int *count_ptr);
void	s_conversion(char *string, int *count_ptr);
void	x_upper_conversion(unsigned int n, int *count_ptr);
void	x_conversion(unsigned int n, int *count_ptr);
void	p_conversion(void *ptr, int *count_ptr);
void	di_conversion(int n, int *count_ptr);
void	u_conversion(unsigned int n, int *count_ptr);
void	function_summary(char c, va_list args, int *i_ptr, int *count_ptr);
void	print_percent(int *i_ptr, int *count_ptr);
void	print_char(int	*i_ptr, char c, int *count_ptr);
void	init_var(int *i, int *count);
void	address_2_hex(size_t n, int *count_ptr);

#endif
