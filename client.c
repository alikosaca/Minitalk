/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akosaca <akosaca@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 05:37:20 by akosaca           #+#    #+#             */
/*   Updated: 2025/02/24 17:21:11 by akosaca          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	set_char(int pid, char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i--;
		usleep(100);
	}
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
		res = res * 10 + str[i++] - 48;
	return (res);
}

int	main(int ac, char *av[])
{
	int		i;

	i = 0;
	if (ac == 3)
	{
		while (av[2][i])
		{
			set_char(ft_atoi(av[1]), av[2][i]);
			i++;
		}
	}
	else
		write(1, "Error: wrong number of arguments\n", 34);
	return (0);
}
