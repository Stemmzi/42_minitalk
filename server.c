/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:39:46 by sgeiger           #+#    #+#             */
/*   Updated: 2024/03/21 17:11:54 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"
#include <unistd.h>

void	recive_byte(int signal)
{
	static int	bit;
	static int	out;
	static size_t	len;
	static size_t	count;

	if (count < (sizeof(size_t) * 8))
	{
		if (signal == SIGUSR1)
			len |= ((size_t)1 << count);
		count++;
	}
	else
	{
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
				ft_printf("%c", out);
				bit = 0;
				out = 0;
				len--;
			}
		}
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = recive_byte;
	ft_printf("%d\n", getpid());
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}