/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flagWorks_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:22:46 by fpedroso          #+#    #+#             */
/*   Updated: 2024/11/27 21:26:31 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	num_flag_help(int *count_p, t_flags flags, int *cont_len, long num);
static void	num_flag_left(int *count_p, t_flags flags, int *cont_len, long num);

void	num_flag(va_list *args_p, int *count_p, t_flags flags, int *cont_len)
{
	long	num;

	num = 0;
	if (flags.conv == 'i' || flags.conv == 'd')
	{
		num = va_arg(*args_p, int);
		if (num < 0)
		{
			*count_p += ft_printchar('-');
			num = -num;
			if (flags.precision > 0)
				*cont_len -= 1;
		}
	}
	else if (flags.conv == 'u' || flags.conv == 'X' || flags.conv == 'x')
		num = va_arg(*args_p, unsigned int);
	else if (flags.conv == 'p')
	{
		num = (long)(uintptr_t)va_arg(*args_p, void *);
		flags.precision = -1;
		*cont_len += 2;
		*count_p += 2;
	}
	num_flag_help(count_p, flags, cont_len, num);
}

static void	num_flag_help(int *count_p, t_flags flags, int *cont_len, long num)
{
	if (flags.conv == 'p' && !num)
	{
		*cont_len -= 2;
		*count_p -= 2;
	}
	if (!flags.l_just)
	{
		if (flags.precision > *cont_len)
		{
			if (flags.precision > flags.width)
				*count_p += print_many('0', (flags.precision - *cont_len));
			else
			{
				*count_p += print_many(' ', (flags.width - flags.precision));
				*count_p += print_many('0', (flags.precision - *cont_len));
			}
		}
		else if (flags.width > *cont_len)
			*count_p += print_many(flags.zero_pad, (flags.width - *cont_len));
		*count_p += printnbr_hub(num, flags.conv);
	}
	else if (flags.l_just)
		num_flag_left(count_p, flags, cont_len, num);
}

static void	num_flag_left(int *count_p, t_flags flags, int *cont_len, long num)
{
	if (flags.precision > *cont_len)
	{
		*count_p += print_many('0', (flags.precision - *cont_len));
		*count_p += printnbr_hub(num, flags.conv);
		if (flags.width > flags.precision)
			*count_p += print_many(' ', (flags.width - flags.precision));
	}
	else
	{
		*count_p += printnbr_hub(num, flags.conv);
		if (flags.width > *cont_len)
			*count_p += print_many(' ', (flags.width - *cont_len));
	}
}

int	printnbr_hub(long num, char conv_type)
{
	if (conv_type == 'i' || conv_type == 'd' || conv_type == 'u')
		return (ft_printnbr(num));
	if (conv_type == 'x' || conv_type == 'X')
		return (print_hex((uintptr_t)num, 0, conv_type));
	if (conv_type == 'p')
	{
		if (!num)
			return (ft_printstr("(nil)", 0));
		ft_printstr("0x", 0);
		return (print_hex((uintptr_t)num, 0, conv_type));
	}
	else
		return (0);
}
