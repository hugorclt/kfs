/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printk.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajung <ajung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:28:31 by ajung             #+#    #+#             */
/*   Updated: 2021/12/01 15:54:47 by ajung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdint.h>

int		what_var(char c, va_list arg_list);
int		printk(const char *str, ...);
int		ft_putnbr_pf(int n);
int		ft_uputnbr_pf(unsigned int n);
int		ft_putstr_pf(char *s);
int		ft_putchar_pf(char c);
int		ft_putnbrbase_pf(unsigned int nb);
int		ft_putnbrbase_maj_pf(unsigned int nb);
int		ft_putnbrlgbase_pf(unsigned long nb);
#endif
