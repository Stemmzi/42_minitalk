/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:39:27 by sgeiger           #+#    #+#             */
/*   Updated: 2024/03/28 16:31:35 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"

void	send_pid(pid_t pid)
{
	size_t	bit;
	pid_t	client_pid;

	bit = 0;
	client_pid = getpid();
	while (bit < (sizeof(pid_t) * 8))
	{
		if ((client_pid & ((pid_t)1 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(150);
		bit++;
	}
}

void	send_len(pid_t pid, size_t len)
{
	size_t	bit;

	bit = 0;
	while (bit < (sizeof(size_t) * 8))
	{
		if ((len & ((size_t)1 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(150);
		bit++;
	}
}

void	send_bits(pid_t pid, char *str)
{
	size_t	bit;
	size_t	count;
	size_t	len;

	bit = 0;
	count = 0;
	len = ft_strlen(str);
	send_pid(pid);
	send_len(pid, len);
	while (count < len)
	{
		while (bit < 8)
		{
			if ((str[count] & (1 << bit)) != 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(150);
			bit++;
		}
		count++;
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
	pid_t	pid;

	if (argc == 3)
	{
		if (ft_strlen(argv[2]) < 1)
		{
			ft_printf("Empty string\n");
			return (1);
		}
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
		ft_printf("Input must be \"./client <pid> <message>\n");
		return (1);
	}
	return (0);
}
