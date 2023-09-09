/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 11:48:49 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/09 15:13:54 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philos_init(t_var *var)
{
	int i;
	i = 0;

	while (i < (var->number_of_philosophers))
	{
		var->philo[i].philo_nbr = i + 1;
		var->philo[i].tm_die = var->tm_die;
		var->philo[i].eaten_times = var->nr_must_eat;
		pthread_mutex_init(&var->philo[i].l_fork, NULL);
		if (i == 0)
			var->philo[i].r_fork = &var->philo[var->number_of_philosophers-1].l_fork;
		else
			var->philo[i].r_fork = &var->philo[i-1].l_fork;
		printf ("info about philo %d: nbr %d, tmdie %d eaten times %d\n",i, var->philo[i].philo_nbr, var->philo[i].tm_die, var->philo[i].eaten_times);
		i++;
	}
	printf ("nbr of philos %d\n", var->number_of_philosophers);


}

void var_init(t_var *var, char **argv)
{
	var->nr_must_eat = 0;
	var->number_of_philosophers = ft_atoi(argv[1]);
	var->tm_die = ft_atoi(argv[2]);
	var->tm_eat = ft_atoi(argv[3]);
	var->tm_sleep = ft_atoi(argv[4]);
	if (argv[5])
		var->nr_must_eat = ft_atoi(argv[5]);
	else
		var->nr_must_eat = -1;
	var->philo = malloc(var->number_of_philosophers * sizeof(t_philo));
	philos_init(var);

	//TODO error handling: zeros or letter
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
	//ft_sleep(1500);

	gettimeofday(&tm_end, NULL);
	printf("Seconds since 1/1/1970: %lu\n",tm_end.tv_sec);
	printf("Microseconds: %d\n",tm_end.tv_usec);
	printf("Milliseconds: %d\n",tm_end.tv_usec/1000);

	tm_passed = (tm_end.tv_usec/1000 + tm_end.tv_sec*1000)  - (tm_start.tv_usec/1000 + tm_start.tv_sec*1000);
	printf("Time passed: %d\n",tm_passed);

	if (argc != 5 && argc != 6)
	{
		ft_putstr_fd("Please pass at least 4 arguments:\n1. number_of_philosophers\n2. time_to_die\n3. time_to_eat\n4. time_to_sleep\n5. number_of_times_each_philosopher_must_eat (optional)", 2);
		return(1);
	}
	if (ft_args_check(argc, argv) == 1)
	{
		ft_putstr_fd("Error: invalid arguments\n", 2);
		return(1);
	}
	var_init(&var, argv);

	printf("number_of_philosophers: %d\n",var.number_of_philosophers);
	printf("tm_die: %d\n",var.tm_die);
	printf("tm_eat: %d\n",var.tm_eat);
	printf("tm_sleep: %d\n",var.tm_sleep);
	printf("nr_must_eat: %d\n",var.nr_must_eat);
	printf ("final info about philo 1: nbr %d, tmdie %d eaten times %d\n", var.philo[1].philo_nbr, var.philo[1].tm_die, var.philo[1].eaten_times);


	return(0);
}


