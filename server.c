/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:39:46 by sgeiger           #+#    #+#             */
/*   Updated: 2024/03/20 23:41:47 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"
#include <unistd.h>

void	recive_byte(int signal)
{
	static int	bit;
	static int	out;

	if (signal == SIGUSR1)
		out |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", out);
		bit = 0;
		out = 0;
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