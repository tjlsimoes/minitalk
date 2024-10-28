/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:38:43 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/28 16:43:06 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	error_check(int k)
{
	if (k == -1)
		exit(1);
}

char	*set_buffer_length(int *length, char length_str[4], int *i)
{
	char	*msg;

	ft_memcpy(length, length_str, 4);
	msg = (char *)ft_calloc(1, *length + 1);
	if (!msg)
	{
		ft_putstr_fd("Error allocating memory for message.", 2);
		exit(1);
	}
	*i = 0;
	return (msg);
}

void	terminate(siginfo_t *sa, int *length, char *msg, int *i)
{
	msg[((*i + 8) / 8) - 1] = '\0';
	ft_printf("%s\n", msg);
	free(msg);
	msg = NULL;
	*i = 0;
	*length = 0;
	kill(sa->si_pid, SIGUSR2);
}

void	handle_sigusr12(int sign, siginfo_t *sa)
{
	static int		i = 1;
	static char		letter = 0;
	static char		length_str[4];
	static int		length = 0;
	static char		*msg;

	if (sign == SIGUSR1)
		letter = (letter << 1) | 0;
	else
		letter = (letter << 1) | 1;
	if (i % 8 == 0 && i != 0)
	{
		if (length != 0)
			msg[i / 8 - 1] = letter;
		else
			length_str[i / 8 - 1] = letter;
		if (i == 4 * 8 && !length)
			msg = set_buffer_length(&length, length_str, &i);
		letter = 0;
		if (i / 8 - 1 == length - 1 && length)
			terminate(sa, &length, msg, &i);
	}
	i++;
	usleep(20);
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
