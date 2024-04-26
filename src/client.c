/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:55:41 by fcoullou          #+#    #+#             */
/*   Updated: 2024/03/27 15:12:42 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_i;

void	sig_h(int sig)
{
	static int	i = 0;

	g_i = 1;
	if (sig == SIGUSR2)
		i++;
	else if (sig == SIGUSR1)
	{
		i++;
		ft_printf("Number of bytes : %d\n", (i / 8) - 1);
	}
}

int	char_bin(char c, int pid)
{
	int	bit_index;
	int	i;

	bit_index = 7;
	i = 0;
	while (bit_index >= 0)
	{
		if ((c >> bit_index) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit_index--;
		while (g_i == 0)
		{
			if (i == 50)
			{
				ft_putstr_fd("No response from server !\n", 2);
				exit(0);
			}
			usleep(1500);
			i++;
		}
		g_i = 0;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	act;
	int					i;

	if (argc != 3)
		return (ft_putstr_fd("Wrong arguments !\n", 2), 0);
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		act.sa_handler = sig_h;
		act.sa_flags = SA_SIGINFO;
		sigemptyset(&act.sa_mask);
		sigaction(SIGUSR2, &act, NULL);
		sigaction(SIGUSR1, &act, NULL);
		i = 0;
		while (argv[2][i])
		{
			char_bin(argv[2][i], pid);
			i++;
		}
		char_bin('\0', pid);
		return (0);
	}
	return (0);
}
