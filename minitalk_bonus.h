/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-l < tjorge-l@student.42lisboa.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:46:19 by tjorge-l          #+#    #+#             */
/*   Updated: 2024/10/28 19:27:06 by tjorge-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H
# include "libft/libft.h"
# include "printf/ft_printf.h"
# include <signal.h>
# include <unistd.h>

typedef struct s_msg
{
	int		length;
	char	*msg;
}	t_msg;

void	error_check(int k);
void	incorrect_usage(void);

#endif