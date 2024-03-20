/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:39:27 by sgeiger           #+#    #+#             */
/*   Updated: 2024/03/20 23:44:24 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

void	send_byte(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit <= 7)
	{
		if ((c & (1 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(1000);
		bit++;
	}
}

int	main(int argc, char *argv[])
{
	int	pid;
	int	count;

	count = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][count] != '\0')
		{
			send_byte(pid, argv[2]);
			count++;
		}
	}
	else
	{
		ft_printf("Input must be \"./client <pid> <message>");
		return (1);
	}
	return (0);
}
