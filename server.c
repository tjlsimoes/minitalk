/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:38:43 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/30 11:11:14 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

void	terminate(int *length, char **msg, int *i)
{
	(*msg)[((*i + 8) / 8) - 1] = '\0';
	ft_printf("%s\n", *msg);
	free(*msg);
	*msg = NULL;
	*i = 0;
	*length = 0;
}

void	check_pid(siginfo_t **sa, int *i, char *letter, t_msg *msg_struct)
{
	static pid_t		pid;

	if ((*sa)->si_pid != pid && i != 0)
	{
		pid = (*sa)->si_pid;
		*i = 1;
		*letter = 0;
		if (msg_struct->msg)
		{
			free(msg_struct->msg);
			msg_struct->msg = NULL;
		}
		msg_struct->length = 0;
	}
}

void	handle_sigusr12(int sign, siginfo_t *sa)
{
	static int		i = 1;
	static char		letter = 0;
	static char		length_str[4];
	static t_msg	msg_struct = {0};

	check_pid(&sa, &i, &letter, &msg_struct);
	letter = (letter << 1) | (sign == SIGUSR2);
	if (i % 8 == 0 && i != 0)
	{
		if (msg_struct.length != 0)
			msg_struct.msg[i / 8 - 1] = letter;
		else
			length_str[i / 8 - 1] = letter;
		if (i == 4 * 8 && !msg_struct.length)
			msg_struct.msg = set_buffer_length(&(msg_struct.length),
					length_str, &i);
		letter = 0;
		if (i / 8 - 1 == msg_struct.length - 1 && msg_struct.length)
			terminate(&(msg_struct.length), &(msg_struct.msg), &i);
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
