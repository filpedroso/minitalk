/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 20:20:34 by fpedroso          #+#    #+#             */
/*   Updated: 2024/11/20 16:42:59 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	deli_rec(long long num, int fd, int *count);

int	ft_putnbr_fd(long n, int fd)
{
	long long	num;
	int			count;

	num = n;
	count = 0;
	if (num < 0)
	{
		num = -num;
		ft_putchar_fd('-', fd);
	}
	deli_rec(num, fd, &count);
	return (count);
}

void	deli_rec(long long num, int fd, int *count)
{
	if (num >= 10)
		deli_rec(num / 10, fd, count);
	ft_putchar_fd(num % 10 + '0', fd);
	(*count)++;
}

/* int main()
{
	ft_putnbr_fd(-123456, 1);
} */
