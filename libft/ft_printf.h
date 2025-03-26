/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:01:17 by fpedroso          #+#    #+#             */
/*   Updated: 2025/01/06 13:29:49 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_flags
{
	int		has_flag;
	int		l_just;
	int		zero_pad;
	int		precision;
	int		width;
	char	conv;
}			t_flags;

int			ft_printf(const char *str, ...) __attribute__((format(printf, 1,
						2)));
int			ft_printchar(char c);
int			ft_printstr(char *s, int trim);
int			ft_printnbr(long n);
int			print_hex(uintptr_t num, int counter, char upper);
int			is_conversion(char c);
int			ft_isdigit(int c);
int			ft_isascii(int c);
size_t		ft_strlen2(const char *s);
void		flag_works(const char **str, va_list *args_p, int *count_p,
				int *cont_len);
void		num_flag(va_list *args_p, int *count_p, t_flags flags,
				int *cont_len);
int			is_flag(char c);
void		init_flags(t_flags *flags);
int			print_many(char c, int amount);
int			num_len(long long num);
int			hex_len(long long num);
int			printnbr_hub(long num, char conv_type);
int			ft_atoi(const char *str);

#endif