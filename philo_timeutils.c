/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_timeutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 12:47:16 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/09 12:48:07 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_time_ms(void)
{
	struct	timeval tm_start;

	gettimeofday(&tm_start, NULL);
	return (tm_start.tv_sec * 1000 + tm_start.tv_usec / 1000);
}

int	ft_sleep(int millisec)
{
	int	tm_start;
	int	tm_end;
	int	tm_passed;

	tm_passed = 0;
	tm_start = ft_get_time_ms();
	while(tm_passed < millisec)
	{
		tm_end = ft_get_time_ms();
		tm_passed = tm_end - tm_start;
	}
	return(0);
}
