/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:39:27 by sgeiger           #+#    #+#             */
/*   Updated: 2024/03/27 20:35:27 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"

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
	send_len(pid, len);
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

int	main(int argc, char *argv[])
{
	int	pid;

	if (argc == 3)
	{
		if (ft_strlen(argv[2]) < 1)
			return (1);
		pid = ft_atoi(argv[1]);
		send_bits(pid, argv[2]);
	}
	else
	{
		ft_printf("Input must be \"./client <pid> <message>");
		return (1);
	}
	return (0);
}
