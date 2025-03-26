/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpedroso <fpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 23:09:48 by fpedroso          #+#    #+#             */
/*   Updated: 2025/02/23 23:19:13 by fpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int sig, siginfo_t *s_info, void *context);
void		check_kill(int pid, int sig);

int	main(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
	{
		ft_putstr_fd("sigaction failed !\n", 2);
		exit(1);
	}
	ft_printf("%d\n", getpid());
	while (1)
		pause();
	return (0);
}

static void	handler(int sig, siginfo_t *s_info, void *context)
{
	static unsigned char	byte;
	static int				index;
	static int				pid;

	(void)context;
	if (s_info->si_pid)
		pid = s_info->si_pid;
	byte |= (sig == SIGUSR1);
	index++;
	if (index == 8)
	{
		if (byte == '\0')
		{
			write(1, "\n", 1);
			check_kill(pid, SIGUSR1);
		}
		else
			write(1, &byte, 1);
		index = 0;
		byte = 0;
	}
	else
		byte = byte << 1;
	check_kill(pid, SIGUSR2);
}

void	check_kill(int pid, int sig)
{
	if (kill(pid, sig) == -1)
	{
		ft_putstr_fd("kill failed !\n", 2);
		ft_printf("kill failed ! PID: %i SIG: %i\n", pid, sig);
		exit(1);
	}
}
