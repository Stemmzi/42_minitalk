/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgeiger <sgeiger@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:39:46 by sgeiger           #+#    #+#             */
/*   Updated: 2024/04/30 20:18:49 by sgeiger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "libft/libft.h"

void	finish_up(char *str, int *count, int *current, int *bit)
{
	if (str != NULL)
	{
		str[*count] = '\0';
		*count = 0;
		ft_printf("%s", str);
		free(str);
		str = NULL;
	}
	else
	{
		*count = 0;
		*bit = 0;
		*current = 0;
	}
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
		finish_up(str, &count, &current, &bit);
	return (len);
}

void	bits_util(int signal, size_t *count, size_t *len, char **str)
{
	if (*count == (sizeof(size_t) * 8))
	{
		*str = (char *)malloc(sizeof(char) * (*len + 1));
		if (*str == NULL)
			exit(EXIT_FAILURE);
		(*count)++;
	}
	if (*count < (sizeof(size_t) * 8))
	{
		if (signal == SIGUSR1)
			*len |= ((size_t)1 << *count);
		(*count)++;
	}
	else
	{
		*len = set_bits(signal, *str, *len);
		if (*len == 0)
			*count = 0;
	}
}

void	recive_bits(int signal, siginfo_t *info, void *context)
{
	static size_t	len;
	static size_t	count;
	static char		*str;
	static pid_t	client_pid;

	context = NULL;
	if (client_pid == 0)
		client_pid = info->si_pid;
	if (client_pid != info->si_pid)
	{
		if (str)
			free(str);
		str = NULL;
		len = 0;
		set_bits(signal, str, len);
		count = 0;
		client_pid = info->si_pid;
		ft_printf("\nError: Last client didn't send the whole message\n");
	}
	bits_util(signal, &count, &len, &str);
	if (len == 0)
		client_pid = 0;
}

int	main(void)
{
	struct sigaction	sig;

	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = recive_bits;
	sigemptyset(&sig.sa_mask);
	ft_printf("Server: %d\n", getpid());
	while (1)
	{
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		pause();
	}
	return (0);
}
