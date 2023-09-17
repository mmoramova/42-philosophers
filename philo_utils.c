/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:26:23 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/17 11:14:44 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(int millisec, t_var *var)
{
	int	tm_end;

	tm_end = ft_time_passed(var->tm_start) + millisec;
	while(ft_time_passed(var->tm_start) < tm_end)
		usleep(200);
	return(0);
}

int	ft_time_passed(struct timeval tm_start)
{
	struct timeval	tm_end;
	suseconds_t		tm_passed;

	gettimeofday(&tm_end, NULL);
	tm_passed = (tm_end.tv_usec/1000 + tm_end.tv_sec*1000) - (tm_start.tv_usec/1000 + tm_start.tv_sec*1000);
	return(tm_passed);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_args_check(int argc, char **argv)
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
			if ((argv[i][j] < 9 || argv[i][j] > 13) && argv[i][j] != 32
				&& (argv[i][j] < '0' || argv[i][j] > '9'))
				return (1);
			j++;
		}
		if (ft_atoi(argv[i]) < 1)
			return (1);
		i++;
	}
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
