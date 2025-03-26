/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: filpedroso <filpedroso@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 12:11:36 by fpedroso          #+#    #+#             */
/*   Updated: 2025/03/26 16:33:55 by filpedroso       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void				messager(int pid, char *msg);
static void				acknowledger(int sig);
static void				send_char(unsigned char c, int pid);
void					check_kill(int pid, int sig);

#define MAX_TIME 50000;

volatile sig_atomic_t	g_flare = 0;

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid;

	if (argc != 3)
		return (ft_printf("Usage: ./client PID message\n"));
	pid = ft_atoi(argv[1]);
	if (!pid)
		return (ft_printf("Wrong PID\n"));
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = acknowledger;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
	{
		ft_putstr_fd("sigaction failed !\n", 2);
		exit(1);
	}
	messager(pid, argv[2]);
	pause();
	return (0);
}

static void	acknowledger(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_printf("message received!");
		exit(0);
	}
	if (sig == SIGUSR2)
		g_flare = 1;
}

static void	messager(int pid, char *msg)
{
	while (*msg)
	{
		send_char((unsigned char)*msg, pid);
		msg++;
	}
	send_char(0, pid);
}

static void	send_char(unsigned char c, int pid)
{
	int	j;
	int	max_time;

	j = 7;
	max_time = MAX_TIME;
	while (j >= 0)
	{
		if ((c >> j) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (g_flare == 0)
		{
			usleep(108);
			if (max_time-- == 0)
			{
				ft_putstr_fd("timeout: server not responding\n", 2);
				exit(1);
			}
		}
		g_flare = 0;
		max_time = MAX_TIME;
		j--;
	}
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
