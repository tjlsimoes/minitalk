/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:38:26 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/28 16:58:58 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	send_signal(unsigned int pid, int c)
{
	if (c == 0)
		error_check(kill(pid, SIGUSR1));
	else
		error_check(kill(pid, SIGUSR2));
	pause();
}

void	send_letter(unsigned int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		send_signal(pid, (c >> i) & 1);
		i--;
	}
}

void	handle_sigusr12(int sign)
{
	if (sign == SIGUSR2)
		write(1, "Message acknowledged by the server.\n", 36);
}

void	send_info(char **argv, char *length_chars)
{
	pid_t	pid;
	int		i;

	i = 0;
	pid = ft_atoi(argv[1]);
	if (pid < 0)
		exit(1);
	while (i <= 3)
	{
		send_letter(pid, length_chars[i]);
		i++;
	}
	i = 0;
	while (argv[2][i])
	{
		send_letter(pid, argv[2][i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					length;
	char				*length_chars;

	if (argc != 3)
		incorrect_usage();
	else
	{
		length = ft_strlen(argv[2]);
		length_chars = (char *)&length;
		sa.sa_sigaction = (void *) handle_sigusr12;
		sa.sa_flags = SA_SIGINFO;
		sigemptyset(&sa.sa_mask);
		error_check(sigaction(SIGUSR1, &sa, NULL));
		error_check(sigaction(SIGUSR2, &sa, NULL));
		send_info(argv, length_chars);
	}
	return (0);
}
