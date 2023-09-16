/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_timeutils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 12:47:16 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/16 15:27:50 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_time_ms(void)
{
	struct	timeval tm_start;

	gettimeofday(&tm_start, NULL);
	return (tm_start.tv_sec * 1000 + tm_start.tv_usec / 1000);
}

int	ft_sleep(int millisec, t_var *var)
{
	int	tm_end;

	tm_end = ft_time_passed(var) + millisec;
	while(ft_time_passed(var) < tm_end)
		usleep(200);
	return(0);
}

int	ft_time_passed(t_var *var)
{
	struct timeval tm_end;
	suseconds_t tm_passed;

	//printf("Seconds since 1/1/1970: %lu\n",var->tm_start.tv_sec);
	//printf("Microseconds: %d\n",var->tm_start.tv_usec);
	//printf("Milliseconds: %d\n",var->tm_start.tv_usec/1000);

	gettimeofday(&tm_end, NULL);
	//printf("Seconds since 1/1/1970: %lu\n",tm_end.tv_sec);
	//printf("Microseconds: %d\n",tm_end.tv_usec);
	//printf("Milliseconds: %d\n",tm_end.tv_usec/1000);

	tm_passed = (tm_end.tv_usec/1000 + tm_end.tv_sec*1000)  - (var->tm_start.tv_usec/1000 + var->tm_start.tv_sec*1000);
	//printf("Time passed: %d\n",tm_passed);
	return(tm_passed);
}
