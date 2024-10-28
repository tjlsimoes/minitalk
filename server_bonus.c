/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:38:43 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/28 11:22:11 by tjorge-l         ###   ########.fr       */
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
	static int		j = 0;
	static char		letter = 0;
	static char		length_str[4];
	static int		length = 0;
	static char		*msg;

	if (sign == SIGUSR1)
		letter = (letter << 1) | 0;
	else
		letter = (letter << 1) | 1;
	if (i == 7)
	{
		if (length != 0)
			msg[j] = letter;
		else
			length_str[j] = letter;
		if (j == 3 && !length)
		{
			ft_memcpy(&length, length_str, 4);
			msg = (char *)ft_calloc(1, length + 1);
			if (!msg)
			{
				ft_putstr_fd("Error allocating memory for message.", 2);
				return ;
			}
			j = -1;
		}
		i = 0;
		letter = 0;
		if (j == length - 1 && length)
		{
			msg[j + 1] = '\0';
			ft_printf("%s\n", msg);
			free(msg);
			msg = NULL;
			j = -1;
			length = 0;
		}
		j++;
	}
	else
		i++;

	kill(sa->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID: %u\n", getpid());
	sa.sa_sigaction = (void *) handle_sigusr12;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	error_check(sigaction(SIGUSR1, &sa, NULL));
	error_check(sigaction(SIGUSR2, &sa, NULL));
	while (1)
		pause();
	return (0);
}
