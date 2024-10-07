/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrlgbase_pf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajung <ajung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 16:31:29 by ajung             #+#    #+#             */
/*   Updated: 2021/12/01 15:45:59 by ajung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putnbrlgbase_pf(unsigned long nb)
{
	int		output;

	output = 0;
	if (nb < 10)
	{
		ft_putchar_pf(nb + '0');
		output++;
	}
	else if (nb < 16)
	{
		ft_putchar_pf(nb + 'a' - 10);
		output ++;
	}
	else
	{
		output += ft_putnbrlgbase_pf(nb / 16);
		output += ft_putnbrlgbase_pf(nb % 16);
	}
	return (output);
}
