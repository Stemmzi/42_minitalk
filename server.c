/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:39:46 by sgeiger           #+#    #+#             */
/*   Updated: 2024/03/27 22:01:48 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"

size_t	finish_up(char *str, int count)
{
	str[count] = '\0';
	count = 0;
	ft_printf("%s", str);
	free(str);
	return (count);
}

size_t	set_bits(int signal, char *str, size_t len)
{
	static int	bit;
	static int	current;
	static int	count;

	if (len > 0)
	{
		if (bit < 8)
		{
			if (signal == SIGUSR1)
				current |= (1 << bit);
			bit++;
		}
		if (bit == 8)
		{
			str[count] = (char)current;
			count++;
			bit = 0;
			current = 0;
			len--;
		}
	}
	if (len == 0)
		count = finish_up(str, count);
	return (len);
}

void	recive_bits(int signal)
{
	static size_t	len;
	static size_t	count;
	static char		*str;

	if (count == (sizeof(size_t) * 8))
	{
		str = (char *)malloc(sizeof(char) * len + 1);
		if (str == NULL)
			exit(EXIT_FAILURE);
		count++;
	}
	if (count < (sizeof(size_t) * 8))
	{
		if (signal == SIGUSR1)
			len |= ((size_t)1 << count);
		count++;
	}
	else
	{
		len = set_bits(signal, str, len);
		if (len == 0)
			count = 0;
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
