/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phautena <phautena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:37:28 by phautena          #+#    #+#             */
/*   Updated: 2024/06/06 12:08:33 by phautena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	print_char(int	*i_ptr, char c, int *count_ptr)
{
	write(1, &c, 1);
	*count_ptr += 1;
	*i_ptr += 1;
}
