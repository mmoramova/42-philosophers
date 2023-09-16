/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:34:15 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/16 18:56:03 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void var_init(t_var *var, char **argv)
{
	var->finish = 0;
	var->number_of_philosophers = ft_atoi(argv[1]);
	var->tm_die = ft_atoi(argv[2]);
	var->tm_eat = ft_atoi(argv[3]);
	var->tm_sleep = ft_atoi(argv[4]);
	if (argv[5] && argv[5] != 0)
		var->nr_must_eat = ft_atoi(argv[5]);
	else
		var->nr_must_eat = -1;
	var->philo = malloc(var->number_of_philosophers * sizeof(t_philo));
	var->threads = malloc(var->number_of_philosophers * sizeof(pthread_t));
	pthread_mutex_init(&var->print, NULL);
	pthread_mutex_init(&var->ready, NULL);
	pthread_mutex_lock(&var->ready);
	gettimeofday(&var->tm_start, NULL);
	philos_init(var);
	threads_init(var);
}

void philos_init(t_var *var)
{
	int i;
	i = 0;

	while (i < (var->number_of_philosophers))
	{
		var->philo[i].philo_nbr = i;
		var->philo[i].tm_die = var->tm_die;
		var->philo[i].eaten_times_left = var->nr_must_eat;
		pthread_mutex_init(&var->philo[i].l_fork, NULL);
		if (i == 0)
			var->philo[i].r_fork = &var->philo[var->number_of_philosophers-1].l_fork;
		else
			var->philo[i].r_fork = &var->philo[i-1].l_fork;
		var->philo[i].var = var;
		i++;
	}
}

int threads_init(t_var *var)
{
	int	i;
	int	a;

	i = 0;
	a = 0;

	while (i < (var->number_of_philosophers))
	{
		a = i;
		if (pthread_create(&var->threads[a], NULL, &routine, &var->philo[a]) != 0)
		{
			//return (ft_error(var, "Creating threads"));
			return(1);
		}
		i++;
	}
	return (0);
}

// int	ft_error(t_var *var, char *str)
// {
// 	printf("Error: %s\n", str);


// 	return (1);
// }
