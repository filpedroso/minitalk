/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:30:17 by fpedroso          #+#    #+#             */
/*   Updated: 2025/01/06 13:29:49 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	percent_work(const char **str, va_list *args_p, int *count_p,
				int *fstr_len);
static int	content_len(const char *str, va_list *args_p);
static int	point_len(uintptr_t point);

int	ft_printf(const char *fstr, ...)
{
	int		count;
	int		fstr_len;
	va_list	args;
	int		cont_len;

	if (!fstr)
		return (-1);
	fstr_len = 0;
	cont_len = 0;
	count = 0;
	va_start(args, fstr);
	while (*fstr)
	{
		if (*fstr == '%')
			cont_len += percent_work(&fstr, &args, &count, &fstr_len);
		else
		{
			count += ft_printchar(*fstr++);
			fstr_len++;
		}
	}
	va_end(args);
	if (count < (cont_len + fstr_len))
		return (-1);
	return (count);
}

static int	percent_work(const char **str, va_list *args_p, int *count_p,
		int *fstr_len)
{
	int			cont_len;
	const char	*copy_s;

	cont_len = 0;
	while (**str == '%' && *(*str + 1) == '%')
	{
		*count_p += ft_printchar('%');
		*str += 2;
		(*fstr_len)++;
		return (cont_len);
	}
	if (**str == '%')
		(*str)++;
	copy_s = *str;
	while (!is_conversion(*copy_s))
		copy_s++;
	cont_len = content_len(copy_s, args_p);
	flag_works(str, args_p, count_p, &cont_len);
	return (cont_len);
}

static int	content_len(const char *str, va_list *args_p)
{
	int		count;
	char	*copy_str;
	va_list	copy_args;

	count = 0;
	va_copy(copy_args, *args_p);
	if (*str == 'c')
		count = 1;
	else if (*str == 's')
	{
		copy_str = va_arg(copy_args, char *);
		if (!copy_str)
			count += 6;
		count += ft_strlen2(copy_str);
	}
	else if (*str == 'i' || *str == 'd')
		count = num_len(va_arg(copy_args, int));
	else if (*str == 'u')
		count = num_len((long long)va_arg(copy_args, unsigned int));
	else if (*str == 'p')
		count = point_len((uintptr_t)va_arg(copy_args, void *));
	else if (*str == 'x' || *str == 'X')
		count = hex_len((long long)va_arg(copy_args, unsigned int));
	va_end(copy_args);
	return (count);
}

static int	point_len(uintptr_t point)
{
	int	len;

	len = 1;
	if (!point)
		return (5);
	while (point >= 16)
	{
		point = point / 16;
		len++;
	}
	return (len);
}

// TODO
//
// work on flag_printer, first compile it to see problems

// percent work returns cont_len
// content_len function comes to main file
// flag_work receives cont_len and deals with non-flag cases as well
// if count < (cont_len + fstr_len) return -1

/* #include "ft_printf.h"
#include <limits.h>
#include <stdio.h>

#define FAIL "************** TEST FAILED *************\n\n"
int	main(void)
{
	int a;
	int b;

	// x tests
	printf("x tests\n");
	printf(" printf out\n%d printf length\n", a = printf("%x", 0));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", 0));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%x", -1));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", -1));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%x", 1));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", 1));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%x", 10));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", 10));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%x", 99));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", 99));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%x", -101));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", -101));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%x", INT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x",
			INT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%x", INT_MIN));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x",
			INT_MIN));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%x", UINT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x",
			UINT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%x %x %x %x", INT_MAX,
			INT_MIN, 0, -42));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x %x %x %x",
			INT_MAX, INT_MIN, 0, -42));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	// X tests
	printf("X tests\n");
	printf(" printf out\n%d printf length\n", a = printf("%X", 0));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", 0));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%X", -1));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", -1));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%X", 1));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", 1));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%X", 10));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", 10));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%X", 99));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", 99));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%X", -101));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X", -101));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%X", INT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X",
			INT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%X", INT_MIN));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X",
			INT_MIN));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%X", UINT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X",
			UINT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%X %X %X %X", INT_MAX,
			INT_MIN, 0, -42));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%X %X %X %X",
			INT_MAX, INT_MIN, 0, -42));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	// c tests
	printf("c tests\n");
	printf(" printf out\n%d printf length\n", a = printf("%c", '0'));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%c", '0'));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %c", '0'));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %c", '0'));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%c ", '0'));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%c ", '0'));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %c ", '0'));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %c ", '0'));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %c", '0' - 256));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %c", '0'
			- 256));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%c ", '0' + 256));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%c ", '0'
			+ 256));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %c %c %c ", '1', '2',
			'3'));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %c %c %c ",
			'1', '2', '3'));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf("%c ", '0' + 256));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%c ", '0'
			+ 256));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %c %c %c ", '1', '2',
			'3'));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %c %c %c ",
			'1', '2', '3'));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	// d & i tests
	printf("d & i tests\n");
	printf(" printf out\n%d printf length\n", a = printf(" %d ", -99));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d ", -99));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %d ", 100));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d ", 100));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %d ", INT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d ",
			INT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %d ", INT_MIN));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d ",
			INT_MIN));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %d ", UINT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %d ",
			UINT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	// p tests
	printf("p tests\n");
	printf(" printf out\n%d printf length\n", a = printf(" %p ", (void *)-1));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p ",
			(void *)-1));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %p ", (void *)1));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p ",
			(void *)1));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %p ", (void *)15));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p ",
			(void *)15));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %p ", (void *)0));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p ",
			(void *)0));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf("p tests\n");
	printf(" printf out\n%d printf length\n", a = printf(" %p ", NULL));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p ",
			NULL));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %p %p ",
			(void *)LONG_MIN, (void *)LONG_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p %p ",
			(void *)LONG_MIN, (void *)LONG_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %p %p ",
			(void *)INT_MIN, (void *)INT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p %p ",
			(void *)INT_MIN, (void *)INT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %p %p ",
			(void *)ULONG_MAX, (void *)-ULONG_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %p %p ",
			(void *)ULONG_MAX, (void *)-ULONG_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	// u tests
	printf("u tests\n");
	printf(" printf out\n%d printf length\n", a = printf(" %u ", -100));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %u ",
			-100));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %u ", INT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %u ",
			INT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %u ", INT_MIN));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %u ",
			INT_MIN));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	printf(" printf out\n%d printf length\n", a = printf(" %u ", UINT_MAX));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf(" %u ",
			UINT_MAX));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);

	unsigned int	u;
	int				num;
	char			*str;
	char			c;

	int pf, fp;
	u = 0xFFFFFFFF;
	num = -42;
	str = "Hello, world!";
	c = 'A';
	// Test unsigned hexadecimal
	pf = printf(">%20.15Xq<\n", u);
	fp = ft_printf(">%20.15Xq<\n", u);
	printf("pf = %d, fp = %d\n\n", pf, fp);
	// Test integer with different flags
	pf = printf(">%-10d<\n", num); // left-justify
	fp = ft_printf(">%-10d<\n", num);
	printf("pf = %d, fp = %d\n\n", pf, fp);

	pf = printf(">%010d<\n", num); // zero-padding
	fp = ft_printf(">%010d<\n", num);
	printf("pf = %d, fp = %d\n\n", pf, fp);


	pf = printf(">%.5d<\n", num); // precision
	fp = ft_printf(">%.5d<\n", num);
	printf("pfzero = %d, fpzero = %d\n\n", pf, fp);

// ####################################################################

	// Test string

	pf = printf(">%.5sq<\n", str); // precision for string
	fp = ft_printf(">%.5sq<\n", str);
	printf("pf = %d, fp = %d\n\n", pf, fp);


	pf = printf(">%-20sq<\n", str); // left-justify with width
	fp = ft_printf(">%-20sq<\n", str);
	printf("pf = %d, fp = %d\n\n", pf, fp);

	printf("###########################################\n\n");

	pf = printf(">%-6p<\n",(void*)0); // width
	fp = ft_printf(">%-6p<\n",(void*)0);
	printf("pf = %d, fp = %d\n\n", pf, fp);
	

	printf("###########################################\n");

	pf = printf(">%-9p<\n", (void*)LONG_MIN); // width
	fp = ft_printf(">%-9p<\n", (void*)LONG_MIN);
	printf("pf = %d, fp = %d\n\n", pf, fp);

	pf = printf("> %.s <\n", ""); // width
	fp = ft_printf("> %.s <\n", "");
	printf("pf = %d, fp = %d\n\n", pf, fp);

// ####################################################################
	pf = printf(">%20sq<\n", str); // width
	fp = ft_printf(">%20sq<\n", str);
	printf("pf = %d, fp = %d\n\n", pf, fp);

	// Test character
	pf = printf(">%-5cq<\n", c); // left-justify
	fp = ft_printf(">%-5cq<\n", c);
	printf("pf = %d, fp = %d\n\n", pf, fp);
	// Test unsigned integer
	pf = printf(">%.10uq<\n", u); // precision
	fp = ft_printf(">%.10uq<\n", u);
	printf("pf = %d, fp = %d\n\n", pf, fp);

	// Test edge cases
	pf = printf(">%.0dq<\n", 0); // zero with precision zero
	fp = ft_printf(">%.0dq<\n", 0);
	printf("pf = %d, fp = %d\n\n", pf, fp);
	pf = printf(">%.0uq<\n", 0); // zero with precision zero (unsigned)
	fp = ft_printf(">%.0uq<\n", 0);
	printf("pf = %d, fp = %d\n\n", pf, fp);

	// Test integer with maximum and minimum values
	pf = printf(">%.20dq<\n", INT_MAX);
	fp = ft_printf(">%.20dq<\n", INT_MAX);
	printf("pf = %d, fp = %d\n\n", pf, fp);
	pf = printf(">%.20dq<\n", INT_MIN);
	fp = ft_printf(">%.20dq<\n", INT_MIN);
	printf("pf = %d, fp = %d\n\n", pf, fp);
	return (0);
} */

/* int	main(void)
{
	char			c;
	char			d;
	unsigned int	u;
	int				pf;
	int				fp;
	int				num;
	char			*s;
	char			*s2;

	s = "@@@";
	s2 = NULL;
	c = 'a';
	d = 'b';
	num = 0x7FFFFFFF;
	u = 0xFFFFFFFF;

	printf("c%%de\n");
	ft_printf("c%%de\n");

	pf = printf("a%pbc%%de%5cfg%-20.15uhij%2sk%-20.15dlm%inop%20.15Xq%xr\n",
			(void *)&c, d, u, s, num, 0, u, u);
	fp = ft_printf("a%pbc%%de%5cfg%-20.15uhij%2sk%-20.15dlm%inop%20.15Xq%xr\n",
			(void *)&c, d, u, s, num, 0, u, u);


	pf = printf(">%20.15Xq<\n", u);
	fp = ft_printf(">%20.15Xq<\n", u);
	printf("pf = %d, fp = %d\n", pf, fp);
	pf = printf("%.3d\n", -1234);
	fp = ft_printf("%.3d\n", -1234);
	printf("pf = %d, fp = %d\n", pf, fp);
	pf = printf("%-9sScience!\n", "Aperture");
	fp = ft_printf("%-9sScience!\n", "Aperture");
	printf("pf = %d, fp = %d\n", pf, fp);


	printf("#########################\n");

	pf = printf(">pf: %8p-<\n", NULL);
	fp = ft_printf(">fp: %8p-<\n", NULL);
	printf("pf = %d, fp = %d\n", pf, fp);

	printf("\n#########################\n\n");

	pf = printf(">pf: %8s<\n", s2);
	fp = ft_printf(">fp: %8s<\n", s2);
	printf("pf = %d, fp = %d\n", pf, fp);

	pf = printf("pf: %8p-%8s\n", NULL, s2);
	fp = ft_printf("fp: %8p-%8s\n", NULL, s2);
	printf("pf = %d, fp = %d\n", pf, fp);



	pf = printf("%i|%i|%i\n", -2147483647 - 1, 0, 0x7FFFFFFF);
	fp = ft_printf("%i|%i|%i\n", -2147483647 - 1, 0, 0x7FFFFFFF);
	printf("pf = %d, fp = %d\n", pf, fp);
	pf = printf("%p-%s\n", NULL, s2);
	fp = ft_printf("%p-%s\n", NULL, s2);
	printf("pf = %d, fp = %d\n", pf, fp);
	pf = printf("printf : a%pbc%%de%cfg%uh%cij%sk%dlm%inop%Xq%xr\n", (void *)&c,
			d, u, '\0', s, num, 0, u, u);
	fp = ft_printf("ftprint: a%pbc%%de%cfg%uh%cij%sk%dlm%inop%Xq%xr\n",
			(void *)&c, d, u, '\0', s, num, 0, u, u);
	printf("pf = %d, fp = %d\n", pf, fp);
	// ERROR handling
	fclose(stdout);
	pf = printf("2printf : a%pbc%%de%cfg%uh%cij%sk%dlm%inop%Xq%xr\n",
			(void *)&c, d, u, '\0', s, num, 0, u, u);
	fp = ft_printf("2ftprint: a%pbc%%de%cfg%uh%cij%sk%dlm%inop%Xq%xr\n",
			(void *)&c, d, u, '\0', s, num, 0, u, u);
	num = write(1, "a\n", 2);
	dprintf(2, "pfd = %d, fp = %d, num = %d\n", pf, fp, num);
	pf = printf(NULL);
	dprintf(2, "pf = %d\n", pf);
	fp = ft_printf(NULL);
	dprintf(2, "fp = %d\n", fp);
	return (0);
} */

/* int	main(void)
{

	ft_printf("3: Width and precision: %.3d\n", 4201);
	ft_printf("4: Left justify: %-10d|\n", 42);


	int ft1 = ft_printf(" %-9X %-10X %-11X %-12X %-13X %-14X %-15X", INT_MAX,
			INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	printf("\nft1: %i", ft1);
	int p1 = printf(" %-9X %-10X %-11X %-12X %-13X %-14X %-15X", INT_MAX,
			INT_MIN, LONG_MAX, LONG_MIN, ULONG_MAX, 0, -42);
	printf("\np1: %i", p1);
	int ft2 = ft_printf(" %2p ", -1);
	printf("\nft2: %i", ft2);
	int p2 = printf(" %2p ", -1);
	printf("\np2: %i", p2);
} */

/* int main(void)
{
	int ret1, ret2;

	// Simple strings
	ret1 = printf("1: Hello, %s!\n", "World");
	ret2 = ft_printf("1: Hello, %s!\n", "World");
	printf("printf: %d, ft_printf: %d\n\n", ret1, ret2);

	// Integers
	ret1 = printf("2: Number: %d\n", 42);
	ret2 = ft_printf("2: Number: %d\n", 42);
	printf("printf: %d, ft_printf: %d\n\n", ret1, ret2);

	// Width and precision
	ret1 = printf("3: Width and precision: %10.5d\n", 42);
	printf("printf: %d, ft_printf: %d\n\n", ret1, ret2);

	// Flags
	ret1 = printf("4: Left justify: %-10d\n", 42);
	ret2 = ft_printf("4: Left justify: %-10d\n", 42);
	printf("printf: %d, ft_printf: %d\n\n", ret1, ret2);

	// Hexadecimal
	ret1 = printf("5: Hex: %#x\n", 255);
	ret2 = ft_printf("5: Hex: %#x\n", 255);
	printf("printf: %d, ft_printf: %d\n\n", ret1, ret2);

	// Pointers
	int num = 42;
	ret1 = printf("6: Pointer: %p\n", &num);
	ret2 = ft_printf("6: Pointer: %p\n", &num);
	printf("printf: %d, ft_printf: %d\n\n", ret1, ret2);

	return (0);
} */

/* #define FAIL "****** TEST FAILED *********\n\n"
#include <limits.h>

int	main(void)
{
	int a;
	int b;


	printf(" printf out\n%d printf length\n", a = printf("%x", 0));
	printf(" ft_printf out\n%d ft_printf length\n", b = ft_printf("%x", 0));
	a == b ? printf("TEST PASSED\n\n") : printf(FAIL);
}*/
