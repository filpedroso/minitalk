/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 00:24:19 by fpedroso          #+#    #+#             */
/*   Updated: 2025/01/06 13:29:49 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	deli_rec(long long num, int *count);

int	ft_printchar(char c)
{
	int	i;

	i = write(1, &c, 1);
	return (i);
}

int	ft_printstr(char *s, int trim)
{
	size_t	buffer;

	if (!s)
	{
		write(1, "(null)", 6);
		return (6);
	}
	if (s[0] == '\0')
		return (0);
	buffer = ft_strlen2(s);
	return (write(1, s, buffer - trim));
}

int	ft_printnbr(long n)
{
	long long	num;
	int			count;

	num = n;
	count = 0;
	if (num < 0)
	{
		num = -num;
		ft_printchar('-');
		count++;
	}
	deli_rec(num, &count);
	return (count);
}

static void	deli_rec(long long num, int *count)
{
	if (num >= 10)
		deli_rec(num / 10, count);
	(*count) += ft_printchar(num % 10 + '0');
}

int	print_hex(uintptr_t num, int counter, char upper)
{
	if (num >= 16)
		counter = print_hex(num / 16, counter, upper);
	if (upper == 'X')
		counter += ft_printchar("0123456789ABCDEF"[num % 16]);
	else
		counter += ft_printchar("0123456789abcdef"[num % 16]);
	return (counter);
}
/*
no truncation
zero-pad (0) ->		left-padding, but ignored if '-' was used,
			or '.' was used on an int.
					prints zeros only if width is bigger than strlen of printed.
precision (.) ->	minimum digits to be printed for iduxX,
					padding with zeros on the left
					for strings means the maximum chars to be printed,
						cropping the string
left-justify (-) ->	left justifies using width, pads with spaces on the right.
width (0-9) ->		specifies width for (-) or (0).

 */