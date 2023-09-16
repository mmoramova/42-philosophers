/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:26:23 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/16 15:27:02 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_args_check(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (ft_strlen(argv[i]) < 1)
			return (1);
		while (argv[i][j])
		{
			if ((argv[i][j] < 9 || argv[i][j] > 13) && argv[i][j] != 32 && (argv[i][j] < '0' || argv[i][j] > '9'))  //?can i have empty spaces
				return (1);
			j++;
		}
		i++;
	}
	if (ft_atoi(argv[1]) < 2) //TODO, one philo
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nbr;
	int	sign;

	nbr = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - '0');
		i++;
	}
	return (nbr * sign);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		ft_putchar_fd(*s++, fd);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
