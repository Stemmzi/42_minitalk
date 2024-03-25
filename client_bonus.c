/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:39:27 by sgeiger           #+#    #+#             */
/*   Updated: 2024/03/25 18:20:19 by sgeiger          ###   ########.fr       */
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
		usleep(100);
		count++;
	}
}

void	send_size(int pid, size_t len)
{
	size_t	count;

	count = 0;
	while (count < (sizeof(size_t) * 8))
	{
		if ((len & ((size_t)1 << count)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
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
	send_size(pid, len);
	while (count2 < len)
	{
		while (bit < 8)
		{
			if ((str[count2] & (1 << bit)) != 0)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
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
		ft_printf("Success!");
		exit(EXIT_SUCCESS);
	}
	else
	{
		ft_printf("Failure!");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char *argv[])
{
	int					pid;
	struct sigaction	sa;

	sa.sa_handler = recive_answer;
	sa.sa_flags = SA_SIGINFO;
	if (argc == 3)
	{
		if (ft_strlen(argv[2]) < 1)
			return (1);
		pid = ft_atoi(argv[1]);
		sigaction(SIGUSR1, &sa, NULL);
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
