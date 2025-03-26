/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:58:49 by fpedroso          #+#    #+#             */
/*   Updated: 2024/11/19 00:10:38 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	buffer;

	if (!s)
		return (0);
	buffer = ft_strlen(s);
	write(fd, s, buffer);
	return ((int)buffer);
}
/* int	main(void)
{
	ft_putstr_fd("jacare", 1);
} */
