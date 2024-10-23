/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:38:43 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/23 11:01:52 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	error_check(int k)
{
	if (k == -1)
		exit(1);
}

// void	reset_variables(int *difference, int *i, char *letter, int sig_sent)
// {
// 	if (sig_sent)
// 		*difference = 0;
// 	else
// 		*difference = 1;
// 	*i = 0;
// 	*letter = 0;
// }

void	handle_sigusr12(int sign, siginfo_t *sa)
{
	static int		i = 0;
	static char		letter = 0;


	if (sign == SIGUSR1)
		letter = (letter << 1) | 0;
	else
		letter = (letter << 1) | 1;
	if (i == 7)
	{
		write(1, &letter, 1);
		i = 0;
		letter = 0;
		// if (difference == 1)
		// 	error_check(kill(pid, SIGUSR2));

	}
	else
		i++;
	kill(sa->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID: %u\n", getpid());
	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = (void *) handle_sigusr12;
	sa.sa_flags = SA_SIGINFO;
	error_check(sigaction(SIGUSR1, &sa, NULL));
	error_check(sigaction(SIGUSR2, &sa, NULL));
	while (1)
		pause();
	return (0);
}
