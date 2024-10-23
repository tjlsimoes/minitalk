/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:38:26 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/23 11:05:57 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	error_check(int k)
{
	if (k == -1)
		exit(1);
}

void	send_signal(unsigned int pid, int c)
{
	if (c == 0)
		error_check(kill(pid, SIGUSR1));
	else
		error_check(kill(pid, SIGUSR2));
}

void	send_letter(unsigned int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		send_signal(pid, (c >> i) & 1);
		usleep(9000);
		i--;
	}
}

void	incorrect_usage(void)
{
		ft_putstr_fd("Correct usage: ./client <PID> \"<MESSAGE>\"\n", 2);
		exit(1);
}

void	handle_sigusr1(int sign)
{
	if (sign == SIGUSR2)
		write(1, "Message acknowledged by the server.\n", 36);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	pid_t	pid;
	int		i;

	if (argc != 3)
		incorrect_usage();
	else
	{
		sa.sa_sigaction = (void *) handle_sigusr1;
		sa.sa_flags = SA_SIGINFO;
		error_check(sigaction(SIGUSR1, &sa, NULL));
		error_check(sigaction(SIGUSR2, &sa, NULL));
		i = 0;
		pid = ft_atoi(argv[1]);
		if (pid < 0)
			exit(1);
		while (argv[2][i])
		{
			send_letter(pid, argv[2][i]);
			i++;
		}
		exit(0);
	}
	return (0);
}
