/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:38:43 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/10 16:30:29 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_sigusr12(int sign)
{
	static int	i = 0;
	static char	letter = 0;

	if (sign == SIGUSR1)
	{
		letter = (letter << 1) | 0;
		// ft_printf("SIGUSR1 received.\n");
	}
	else
	{
		// ft_printf("SIGUSR2 received.\n");
		letter = (letter << 1) | 1;
	}
	// ft_printf("%d\n", i);
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
	struct sigaction sa;
	
	ft_printf("PID: %u\n", getpid());

	ft_bzero(&sa, sizeof(sa));
	// sa.sa_sigaction = handle_sigusr12;
	sa.sa_handler = &handle_sigusr12;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}