/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:34:15 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/17 13:57:08 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	var_init(t_var *var, char **argv)
{
	var->game_finished = 0;
	var->philos_finished = 0;
	var->number_of_philosophers = ft_atoi(argv[1]);
	var->tm_die = ft_atoi(argv[2]);
	var->tm_eat = ft_atoi(argv[3]);
	var->tm_sleep = ft_atoi(argv[4]);
	if (argv[5] && argv[5] != 0)
		var->times_must_eat = ft_atoi(argv[5]);
	else
		var->times_must_eat = -1;
	var->philo = malloc(var->number_of_philosophers * sizeof(t_philo));
	var->threads = malloc(var->number_of_philosophers * sizeof(pthread_t));
	pthread_mutex_init(&var->mutex_print, NULL);
	pthread_mutex_init(&var->mutex_game_ready, NULL);
	pthread_mutex_init(&var->mutex_game_finished, NULL);
	pthread_mutex_init(&var->mutex_philos_finished, NULL);
	pthread_mutex_lock(&var->mutex_game_ready);
	gettimeofday(&var->tm_start, NULL);
	philos_init(var);
	threads_init(var);
}

void	philos_init(t_var *var)
{
	int	i;

	i = 0;
	while (i < (var->number_of_philosophers))
	{
		var->philo[i].philo_nbr = i;
		var->philo[i].tm_die = var->tm_die;
		var->philo[i].eaten_times_left = var->times_must_eat;
		pthread_mutex_init(&var->philo[i].l_fork, NULL);
		if (i == 0)
			var->philo[i].r_fork
				= &var->philo[var->number_of_philosophers - 1].l_fork;
		else
			var->philo[i].r_fork = &var->philo[i - 1].l_fork;
		pthread_mutex_init(&var->philo[i].mutex_tm_die, NULL);
		var->philo[i].var = var;
		i++;
	}
}

int	threads_init(t_var *var)
{
	int	i;
	int	a;

	i = 0;
	a = 0;
	while (i < (var->number_of_philosophers))
	{
		a = i;
		if (pthread_create(&var->threads[a], NULL,
				&routine, &var->philo[a]) != 0)
		{
			printf("Error: Creating threads\n");
			return (1);
		}
		i++;
	}
	return (0);
}
