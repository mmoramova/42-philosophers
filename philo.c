/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 11:48:49 by mmoramov          #+#    #+#             */
/*   Updated: 2023/06/25 15:52:16 by mmoramov         ###   ########.fr       */
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
	var.tm_die = ft_atoi(argv[2]);
	var.tm_eat = ft_atoi(argv[3]);
	var.tm_sleep = ft_atoi(argv[4]);
	if(argv[5])
		var.nr_must_eat = ft_atoi(argv[5]);
	else
		var.nr_must_eat = -1;

	//TODO error handling: zeros
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

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Please pass these 4 arguments:\n1. number_of_philosophers\n2. time_to_die\n3. time_to_eat\n4. time_to_sleep\n5. number_of_times_each_philosopher_must_eat (optional)", 2);
		return(1);
	}
	if (ft_args_check(argc, argv) == 1)
	{
		ft_putstr_fd("Error: invalid arguments\n", 2);
		return(1);
	}
	var = args_init(argv);

	printf("number_of_philosophers: %d\n",var.number_of_philosophers);
	printf("tm_die: %d\n",var.tm_die);
	printf("tm_eat: %d\n",var.tm_eat);
	printf("tm_sleep: %d\n",var.tm_sleep);
	printf("nr_must_eat: %d\n",var.nr_must_eat);
	return(0);
}
