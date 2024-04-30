/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:39:27 by sgeiger           #+#    #+#             */
/*   Updated: 2024/04/30 20:03:47 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"

void	send_len(int pid, size_t len)
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

void	send_bits(int pid, char *str)
{
	int		bit;
	size_t	count;
	size_t	len;

	bit = 0;
	count = 0;
	len = ft_strlen(str);
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

int	input_checker(char *pid)
{
	int	len;
	int	count;

	len = ft_strlen(pid);
	count = 0;
	if (pid[count] == '+' || pid[count] == '-')
		return (1);
	while (count < len)
	{
		if (!ft_isdigit(pid[count]))
			return (1);
		count++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc == 3)
	{
		if (ft_strlen(argv[2]) < 1)
		{
			ft_printf("Error: Empty string\n");
			return (1);
		}
		if (input_checker(argv[1]))
		{
			ft_printf("Error: Check your PID\n");
			return (1);
		}
		pid = ft_atoi(argv[1]);
		send_bits(pid, argv[2]);
	}
	else
	{
		ft_printf("Error: Input must be \"./client <pid> <message>\n");
		return (1);
	}
	return (0);
}
