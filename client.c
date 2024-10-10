/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:38:26 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/10 16:30:40 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_signal(unsigned int pid, int c)
{
	if (c == 0)
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	usleep(200);
	usleep(200);
	// ft_printf("Sending signal...\n");
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
	int 	i;

	if (argc != 3)
		return (1); // Error handling
	else
	{
		i = 0;
		while (argv[2][i] != '\0')
		{
			send_letter(ft_atoi(argv[1]), argv[2][i]);
			i++;
		}
	}
	return (0);
}
