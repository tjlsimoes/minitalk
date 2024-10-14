/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:38:26 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/14 11:24:49 by tjorge-l         ###   ########.fr       */
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
	usleep(200);
	usleep(200);
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

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	if (argc != 3)
	{
		ft_putstr_fd("Correct usage: ./client <PID> \"<MESSAGE>\"\n", 2);
		exit(1);
	}
	else
	{
		i = 0;
		pid = ft_atoi(argv[1]);
		if (pid < 0)
			exit(1);
		while (argv[2][i] != '\0')
		{
			send_letter(pid, argv[2][i]);
			i++;
		}
	}
	return (0);
}
