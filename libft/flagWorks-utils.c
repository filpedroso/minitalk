/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagWorks-utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:29:54 by fpedroso          #+#    #+#             */
/*   Updated: 2024/11/27 20:38:38 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_flag(char c)
{
	return (ft_isdigit(c) || c == '-' || c == '.' || c == '0');
}

void	init_flags(t_flags *flags)
{
	flags->has_flag = 0;
	flags->l_just = 0;
	flags->zero_pad = ' ';
	flags->precision = -1;
	flags->width = 0;
	flags->conv = '\0';
}

int	print_many(char c, int amount)
{
	int	count;

	if (amount <= 0)
		return (0);
	count = 0;
	while (amount)
	{
		count += write(1, &c, 1);
		amount--;
	}
	return (count);
}

int	num_len(long long num)
{
	int	len;
	int	minus_flag;

	minus_flag = 0;
	len = 1;
	if (num < 0)
	{
		num = -num;
		minus_flag = 1;
	}
	while (num >= 10)
	{
		num = num / 10;
		len++;
	}
	return (len + minus_flag);
}

int	hex_len(long long num)
{
	int	len;
	int	minus_flag;

	minus_flag = 0;
	len = 1;
	if (num < 0)
	{
		num = num * -num;
		minus_flag = 1;
	}
	while (num >= 16)
	{
		num = num / 16;
		len++;
	}
	return (len + minus_flag);
}
