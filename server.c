/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:39:46 by sgeiger           #+#    #+#             */
/*   Updated: 2024/03/27 18:38:44 by sgeiger          ###   ########.fr       */
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

size_t	set_bits(int signal, char	*str, size_t len)
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
		count = finish_up(str, count);
	return (len);
}

void	recive_bits(int signal)
{
	static size_t	len;
	static size_t	count;
	static char		*str;
	static int		flag;

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
		{
			count = 0;
			flag = 0;
		}
	}
	if (flag == 0 && count == (sizeof(size_t) * 8))
	{
		str = (char *)malloc(sizeof(char) * len + 1);
		flag = 1;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = recive_bits;
	ft_printf("%d\n", getpid());
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}
