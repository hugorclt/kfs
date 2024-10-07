/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajung <ajung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 19:26:04 by ajung             #+#    #+#             */
/*   Updated: 2021/12/01 15:50:51 by ajung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printk.h"
#include "vga.h"

static int	is_int_min(void);

int	ft_putnbr_pf(int n)
{
	int		output;

	output = 0;
	if (n == -2147483648)
		return (is_int_min());
	if (n < 0)
	{
		n = -n;
		vga_write_buffer('-');
		output++;
	}
	if (n < 10)
	{
		ft_putchar_pf(n + '0');
		output++;
	}
	else
	{
		output += ft_putnbr_pf(n / 10);
		output += ft_putnbr_pf(n % 10);
	}
	return (output);
}

static int	is_int_min(void)
{
	vga_write_buffer_str("-2147483648");
	return (11);
}

int	ft_uputnbr_pf(unsigned int n)
{
	int		output;

	output = 0;
	if (n < 10)
	{
		ft_putchar_pf(n + '0');
		output++;
	}
	else
	{
		output += ft_putnbr_pf(n / 10);
		output += ft_putnbr_pf(n % 10);
	}
	return (output);
}
