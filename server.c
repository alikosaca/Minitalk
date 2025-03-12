/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 05:37:17 by akosaca           #+#    #+#             */
/*   Updated: 2025/03/01 13:08:44 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putpid(int n)
{
	char	c;

	if (n > 9)
	{
		ft_putpid((n / 10));
		ft_putpid((n % 10));
	}
	else
	{
		c = 48 + n;
		write(1, &c, 1);
	}
}

void	write_c(int mybit)
{
	static int	i;
	static char	c;

	c = c << 1;
	if (mybit == SIGUSR1)
		c = c | 1;
	i++;
	if (i == 8)
	{
		write(1, &c, 1);
		i = 0;
		c = 0;
	}
}

int	main(void)
{
	write(1, "Server starter. PID: ", 20);
	ft_putpid(getpid());
	while (1)
	{
		signal(SIGUSR1, write_c);
		signal(SIGUSR2, write_c);
	}
}
