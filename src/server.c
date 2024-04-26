/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcoullou <fcoullou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 16:55:50 by fcoullou          #+#    #+#             */
/*   Updated: 2024/03/27 14:06:08 by fcoullou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char	bin_char(int sig, char *c)
{
	if (sig == SIGUSR1)
		*c = (*c << 1) | 1;
	else if (sig == SIGUSR2)
		*c <<= 1;
	return (*c);
}

char	*char_str(char c)
{
	static char	*str = NULL;
	char		*tmp;
	int			s;

	s = ft_strlen(str);
	tmp = str;
	if (c)
	{
		str = ft_strjoinchar(tmp, c);
		free(tmp);
		if (!str)
			return (NULL);
	}
	return (str);
}

void	sig_handlr(int sig, siginfo_t *info, void *context)
{
	static int		i = 0;
	static char		c = 0;
	char			*str;
	static int		pid = 0;

	(void)context;
	pid = info->si_pid;
	bin_char(sig, &c);
	if (++i == 8)
	{
		if (c == '\0')
		{
			str = char_str(c);
			clean_exit(str);
			ft_printf("%s\n", str);
			kill(pid, SIGUSR1);
			ft_memset(str, 0, ft_strlen(str));
		}
		char_str(c);
		i = 0;
		c = 0;
	}
	kill(pid, SIGUSR2);
}

int	main(void)
{
	int					pid;
	struct sigaction	s_a;

	pid = getpid();
	ft_printf("The PID is %d\n", pid);
	ft_memset(&s_a, 0, sizeof(s_a));
	s_a.sa_sigaction = &sig_handlr;
	s_a.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_a, NULL);
	sigaction(SIGUSR2, &s_a, NULL);
	while (1)
		pause();
	return (0);
}
