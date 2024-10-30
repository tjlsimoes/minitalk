/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 16:57:53 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/28 16:59:01 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

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
