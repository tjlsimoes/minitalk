/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:38:43 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/28 16:25:45 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

void	error_check(int k)
{
	if (k == -1)
		exit(1);
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
	ft_printf("i = %d\n", i);
	if (i % 8 == 0 && i != 0)
	{
		ft_printf("Inside conditon: i == %d\n", i);
		if (length != 0)
		{
			msg[i / 8 - 1] = letter;
			ft_printf("Char added: %c | %c to index %d\n", letter, msg[i / 8 - 1], i / 8 - 1);
		}
		else
			length_str[i / 8 - 1] = letter;
		if (i == 4 * 8 && !length)
		{
			ft_memcpy(&length, length_str, 4);
			ft_printf("Length: %d\n", length);
			msg = (char *)ft_calloc(1, length + 1);
			if (!msg)
			{
				ft_putstr_fd("Error allocating memory for message.", 2);
				return ;
			}
			i = 0;
		}
		letter = 0;
		if (i / 8 - 1 == length - 1 && length)
		{
			ft_printf("Final index: %d\n", ((i + 8) / 8) - 1);
			msg[((i + 8) / 8) - 1] = '\0';
			ft_printf("%s\n", msg);
			free(msg);
			msg = NULL;
			i = 0;
			length = 0;
			kill(sa->si_pid, SIGUSR2);
		}
	}
	i++;
	usleep(10);
	usleep(10);
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
