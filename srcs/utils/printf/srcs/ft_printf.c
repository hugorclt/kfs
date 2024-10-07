/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajung <ajung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:30:24 by ajung             #+#    #+#             */
/*   Updated: 2021/12/02 18:44:16 by ajung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"
#include "vga.h"

int	ft_printf(const char *str, ...)
{
	va_list	arg_list;
	int		i;
	int		result;

	va_start(arg_list, str);
	i = 0;
	result = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			result += what_var(str[i], arg_list);
		}
		else
		{
			ft_putchar_pf(str[i]);
			result++;
		}
		i++;
	}
	va_end(arg_list);
	return (result);
}

int	what_var(char c, va_list arg_list)
{
	if (c == 'c')
		return (ft_putchar_pf((char)va_arg(arg_list, int)));
	else if (c == '%')
		return (ft_putchar_pf('%'));
	else if (c == 's')
		return (ft_putstr_pf(va_arg(arg_list, char *)));
	else if (c == 'p')
	{
		vga_write_buffer_str("0x");
		return (2 + ft_putnbrlgbase_pf(va_arg(arg_list, unsigned long)));
	}
	else if (c == 'i' || c == 'd')
		return (ft_putnbr_pf(va_arg(arg_list, int)));
	else if (c == 'u')
		return (ft_uputnbr_pf(va_arg(arg_list, unsigned int)));
	else if (c == 'x')
		return (ft_putnbrbase_pf(va_arg(arg_list, unsigned int)));
	else if (c == 'X')
		return (ft_putnbrbase_maj_pf(va_arg(arg_list, unsigned int)));
	return (0);
}
