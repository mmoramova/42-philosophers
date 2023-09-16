/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 11:48:49 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/16 20:48:32 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_line(t_philo *aux, char *s)
{
	int	i;

	i = ft_time_passed(aux->var);
	pthread_mutex_lock(&aux->var->ready);
	if (aux->var->finish != 1)
		printf("%d %d %s\n", i, aux->philo_nbr + 1, s);
	pthread_mutex_unlock(&aux->var->ready);
}

void *routine(void *arg)
{
	t_philo	*aux;
	int		i;
	int		finish;

	aux = (t_philo *)arg;
	finish = 0;
	pthread_mutex_lock(&aux->var->ready);
	pthread_mutex_unlock(&aux->var->ready);
	if ((aux->philo_nbr) % 2 == 1)
	{
		ft_sleep(1, aux->var);
		pthread_mutex_lock(&aux->var->ready);
		pthread_mutex_unlock(&aux->var->ready);
	}
	i = 0;
	while (aux->var->finish != 1)
	{
		if (aux->var->number_of_philosophers == 1)
			continue;
		pthread_mutex_lock(&aux->l_fork);
		pthread_mutex_lock(aux->r_fork);
		ft_print_line(aux, FORK);
		ft_print_line(aux, FORK);
		aux->tm_die = ft_time_passed(aux->var) + aux->var->tm_die;
		ft_print_line(aux, EAT);
		ft_sleep(aux->var->tm_eat, aux->var);
		if (aux->eaten_times_left > 0)
			aux->eaten_times_left--;
		pthread_mutex_unlock(&aux->l_fork);
		pthread_mutex_unlock(aux->r_fork);
		ft_print_line(aux, SLEEP);
		ft_sleep(aux->var->tm_sleep, aux->var);
		ft_print_line(aux, THINK);
	}
	return (void*) 0;
}

void monitor(t_var *var)
{
	int		i;
	int		philo_finished_eaten;

	i = 0;
	philo_finished_eaten = 0;
	while (i < var->number_of_philosophers)
	{
			if (ft_time_passed(var) >= var->philo[i].tm_die)
			{
				ft_print_line(&var->philo[i], DIE);
				var->finish = 1;
				break;
			}
			if (var->nr_must_eat != -1)
			{
				if (var->philo[i].eaten_times_left == 0)
					philo_finished_eaten++;
				if (philo_finished_eaten == var->number_of_philosophers)
				{
					var->finish = 1;
					break;
				}
				i++;
				if (i == var->number_of_philosophers)
				{
					i = 0;
					philo_finished_eaten = 0;
				}
			}
	}
}

int	main(int argc, char **argv)
{
	t_var	var;
	int		i;

	if (argc != 5 && argc != 6)
	{
		printf("Please pass at least 4 arguments:\n1. number_of_philosophers\n2. time_to_die\n3. time_to_eat\n4. time_to_sleep\n5. number_of_times_each_philosopher_must_eat (optional)");
		return (1);
	}
	if (ft_args_check(argc, argv) == 1)
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	var_init(&var, argv);
	ft_sleep(1, &var);
	pthread_mutex_unlock(&var.ready);
	gettimeofday(&var.tm_start, NULL);
	monitor(&var);
	i = 0;
	while (i < (var.number_of_philosophers))
	{
		if (pthread_join(var.threads[i], NULL) != 0)
		{
			return (2);
		}
		i++;
	}
	i = 0;
	while (i < (var.number_of_philosophers))
	{
		pthread_mutex_destroy(&var.philo[i].l_fork);
		i++;
	}
	pthread_mutex_destroy(&var.print);
	pthread_mutex_destroy(&var.ready);
	free(var.philo);
	free(var.threads);
	return (0);
}
