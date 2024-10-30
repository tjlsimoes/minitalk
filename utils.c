/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l <tjorge-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:03:39 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/30 11:07:01 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error_check(int k)
{
	if (k == -1)
		exit(1);
}
void	incorrect_usage(void)
{
	ft_putstr_fd("Correct usage: ./client <PID> \"<MESSAGE>\"\n", 2);
	exit(1);
}
