/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:38:43 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/14 11:24:42 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	error_check(int k)
{
	if (k == -1)
		exit(1);
}

void	handle_sigusr12(int sign, siginfo_t *sa, void *context)
{
	static int		i = 0;
	static char		letter = 0;
	static pid_t	pid;

	(void)context;
	if (sa->si_pid != pid)
	{
		pid = sa->si_pid;
		i = 0;
		letter = 0;
	}
	if (sign == SIGUSR1)
		letter = (letter << 1) | 0;
	else
		letter = (letter << 1) | 1;
	if (i == 7)
	{
		write(1, &letter, 1);
		i = 0;
		letter = 0;
	}
	else
		i++;
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID: %u\n", getpid());
	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = handle_sigusr12;
	sa.sa_flags = SA_SIGINFO;
	error_check(sigaction(SIGUSR1, &sa, NULL));
	error_check(sigaction(SIGUSR2, &sa, NULL));
	while (1)
		pause();
	return (0);
}
