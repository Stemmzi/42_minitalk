/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:39:27 by sgeiger           #+#    #+#             */
/*   Updated: 2024/03/27 18:37:49 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"

void	send_pid(int pid)
{
	size_t	count;
	int		cpid;

	count = 0;
	cpid = getpid();
	while (count < (sizeof(int) * 8))
	{
		if ((cpid & ((size_t)1 << count)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(150);
		count++;
	}
}

void	send_len(int pid, size_t len)
{
	size_t	count;

	count = 0;
	while (count < (sizeof(size_t) * 8))
	{
		if ((len & ((size_t)1 << count)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(150);
		count++;
	}
}

void	send_bits(int pid, char *str)
{
	int		bit;
	size_t	count2;
	size_t	len;

	bit = 0;
	count2 = 0;
	len = ft_strlen(str);
	send_pid(pid);
	send_len(pid, len);
	while (count2 < len)
	{
		while (bit < 8)
		{
			if ((str[count2] & (1 << bit)) != 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(150);
			bit++;
		}
		count2++;
		bit = 0;
	}
}

void	recive_answer(int signal)
{
	if (signal == SIGUSR1)
	{
		ft_printf("Success!\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_printf("Failure!\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[])
{
	int					pid;

	if (argc == 3)
	{
		if (ft_strlen(argv[2]) < 1)
			return (1);
		pid = ft_atoi(argv[1]);
		signal(SIGUSR1, recive_answer);
		signal(SIGUSR2, recive_answer);
		while (1)
		{
			send_bits(pid, argv[2]);
			pause();
		}
	}
	else
	{
		ft_printf("Input must be \"./client <pid> <message>");
		return (1);
	}
	return (0);
}
