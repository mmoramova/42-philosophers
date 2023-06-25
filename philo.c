/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 11:48:49 by mmoramov          #+#    #+#             */
/*   Updated: 2023/06/25 13:33:27 by mmoramov         ###   ########.fr       */
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

t_var	args_init(char **argv)
{
	t_var	var;

	var.number_of_philosophers = ft_atoi(argv[1]);
	var.time_to_die = ft_atoi(argv[2]);
	var.time_to_eat = ft_atoi(argv[3]);
	var.time_to_sleep = ft_atoi(argv[4]);

	//TODO error handling if inputs are correct
	return	(var);
}

int	main(int argc, char **argv)
{
	struct timeval tm_start;
	struct timeval tm_end;
	suseconds_t tm_passed;
	t_var var;

	gettimeofday(&tm_start, NULL);

	printf("Seconds since 1/1/1970: %lu\n",tm_start.tv_sec);
	printf("Microseconds: %d\n",tm_start.tv_usec);
	printf("Milliseconds: %d\n",tm_start.tv_usec/1000);

	//usleep(1000);
	ft_sleep(100);

	gettimeofday(&tm_end, NULL);
	printf("Seconds since 1/1/1970: %lu\n",tm_end.tv_sec);
	printf("Microseconds: %d\n",tm_end.tv_usec);
	printf("Milliseconds: %d\n",tm_end.tv_usec/1000);

	tm_passed = (tm_end.tv_usec/1000 + tm_end.tv_sec*1000)  - (tm_start.tv_usec/1000 + tm_start.tv_sec*1000);
	printf("Time passed: %d\n",tm_passed);

	if (argc != 5) //TODO 6th
		return(1); //TODO error
	var = args_init(argv);

	printf("number_of_philosophers: %d\n",var.number_of_philosophers);
	printf("time_to_die: %d\n",var.time_to_die);
	printf("time_to_eat: %d\n",var.time_to_eat);
	printf("time_to_sleep: %d\n",var.time_to_sleep);
	return(0);
}
