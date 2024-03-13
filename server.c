/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 22:15:48 by sgeiger           #+#    #+#             */
/*   Updated: 2024/03/13 18:48:04 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"
#include <unistd.h>

void	handler(int num)
{
	if (num == SIGUSR1)
	{
		write(1, "0", 1);
	}
	if (num == SIGUSR2)
	{
		write(1, "1", 1);
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = handler;
	ft_printf("%d\n", getpid());
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}
