/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:19:00 by pbailly           #+#    #+#             */
/*   Updated: 2024/11/07 13:46:57 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>
# include "libft.h"

int	ft_printf(const char *str, ...);
int	ft_printfchar(char c);
int	ft_printfstr(char *str);
int	ft_printfnbr(int n);
int	ft_printf_unsigned_nbr(unsigned int n);
int	ft_printf_x(unsigned int n, char form);
int	ft_printf_p(void *n, char form);

#endif
