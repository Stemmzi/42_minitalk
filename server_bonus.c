/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:39:46 by sgeiger           #+#    #+#             */
/*   Updated: 2024/03/28 18:47:41 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"

size_t	finish_up(char *str, int count, pid_t pid)
{
	str[count] = '\0';
	count = 0;
	kill(pid, SIGUSR1);
	usleep(150);
	ft_printf("%s", str);
	free(str);
	return (count);
}

size_t	set_bits(int signal, char *str, size_t len, pid_t pid)
{
	static int	bit;
	static int	out;
	static int	count;

	if (len > 0)
	{
		if (bit < 8)
		{
			if (signal == SIGUSR1)
				out |= (1 << bit);
			bit++;
		}
		if (bit == 8)
		{
			str[count] = (char)out;
			count++;
			bit = 0;
			out = 0;
			len--;
		}
	}
	if (len == 0)
		count = finish_up(str, count, pid);
	return (len);
}

int	set_lenpid(int signal, size_t *len, pid_t *pid, int *flag)
{
	static size_t	count;
	static size_t	countlen;

	if (*flag == 1)
	{
		*flag = 0;
		count = 0;
		countlen = 0;
	}
	if (count < (sizeof(pid_t) * 8))
	{
		if (signal == SIGUSR1)
			*pid |= ((pid_t)1 << count);
		count++;
		return (1);
	}
	else if (count < ((sizeof(size_t) * 8) + (sizeof(pid_t) * 8)))
	{
		if (signal == SIGUSR1)
			*len |= ((size_t)1 << countlen);
		count++;
		countlen++;
		return (1);
	}
	return (0);
}

void	recive_bits(int signal)
{
	static size_t	len;
	static pid_t	pid;
	static size_t	count;
	static char		*str;
	static int		flag;

	if (count == (sizeof(size_t) * 8) + (sizeof(pid_t) * 8))
	{
		str = ((char *)malloc(sizeof(char) * len + 1));
		if (!str && (kill(pid, SIGUSR2) == 0))
			exit(EXIT_FAILURE);
		count++;
	}
	if (set_lenpid(signal, &len, &pid, &flag) == 1)
		count++;
	else
	{
		len = set_bits(signal, str, len, pid);
		if (len == 0)
		{
			flag = 1;
			count = 0;
			pid = 0;
		}
	}
}

int	main(void)
{
	ft_printf("%d\n", getpid());
	while (1)
	{
		signal(SIGUSR1, recive_bits);
		signal(SIGUSR2, recive_bits);
		pause();
	}
	return (0);
}
