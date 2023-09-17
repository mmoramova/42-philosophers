/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 13:43:38 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/17 13:58:15 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*aux;
	int		i;
	int		game_finished;

	aux = (t_philo *)arg;
	pthread_mutex_lock(&aux->var->mutex_game_ready);
	pthread_mutex_unlock(&aux->var->mutex_game_ready);
	if ((aux->philo_nbr) % 2 == 1)
	{
		ft_sleep(1, aux->var);
		pthread_mutex_lock(&aux->var->mutex_game_ready);
		pthread_mutex_unlock(&aux->var->mutex_game_ready);
	}
	i = 0;
	game_finished = 0;
	while (game_finished != 1)
	{
		if (aux->var->number_of_philosophers != 1)
			routine_eating(aux);
		pthread_mutex_lock(&aux->var->mutex_game_finished);
		game_finished = aux->var->game_finished;
		pthread_mutex_unlock(&aux->var->mutex_game_finished);
	}
	return ((void *) 0);
}

void	routine_eating(t_philo *aux)
{
	pthread_mutex_lock(&aux->l_fork);
	pthread_mutex_lock(aux->r_fork);
	ft_print_line(aux, FORK);
	ft_print_line(aux, FORK);
	pthread_mutex_lock(&aux->mutex_tm_die);
	aux->tm_die = ft_time_passed(aux->var->tm_start) + aux->var->tm_die;
	pthread_mutex_unlock(&aux->mutex_tm_die);
	ft_print_line(aux, EAT);
	ft_sleep(aux->var->tm_eat, aux->var);
	if (aux->var->times_must_eat > 0 && aux->eaten_times_left > 0)
	{
		aux->eaten_times_left--;
		if (aux->eaten_times_left == 0)
		{
			pthread_mutex_lock(&aux->var->mutex_philos_finished);
			aux->var->philos_finished++;
			pthread_mutex_unlock(&aux->var->mutex_philos_finished);
		}
	}
	pthread_mutex_unlock(&aux->l_fork);
	pthread_mutex_unlock(aux->r_fork);
	ft_print_line(aux, SLEEP);
	ft_sleep(aux->var->tm_sleep, aux->var);
	ft_print_line(aux, THINK);
}

void	monitor(t_var *var)
{
	int		i;
	int		philo_tm_die;

	i = 0;
	while (i < var->number_of_philosophers)
	{
		pthread_mutex_lock(&var->philo[i].mutex_tm_die);
		philo_tm_die = var->philo[i].tm_die;
		pthread_mutex_unlock(&var->philo[i].mutex_tm_die);
		if (ft_time_passed(var->tm_start) >= philo_tm_die)
		{
			ft_print_line(&var->philo[i], DIE);
			pthread_mutex_lock(&var->mutex_game_finished);
			var->game_finished = 1;
			pthread_mutex_unlock(&var->mutex_game_finished);
			break ;
		}
		if (var->times_must_eat > 0 && monitor_times_eaten(var) == 1)
			break ;
		i++;
		if (i == var->number_of_philosophers)
			i = 0;
		usleep (100);
	}
}

int	monitor_times_eaten(t_var *var)
{
	int		philos_finished_eaten;

	philos_finished_eaten = 0;
	pthread_mutex_lock(&var->mutex_philos_finished);
	philos_finished_eaten = var->philos_finished;
	pthread_mutex_unlock(&var->mutex_philos_finished);
	if (philos_finished_eaten == var->number_of_philosophers)
	{
		pthread_mutex_lock(&var->mutex_game_finished);
		var->game_finished = 1;
		pthread_mutex_unlock(&var->mutex_game_finished);
		return (1);
	}
	return (0);
}

void	ft_finish(t_var *var)
{
	int	i;

	i = 0;
	while (i < (var->number_of_philosophers))
	{
		if (pthread_join(var->threads[i++], NULL) != 0)
		{
			printf("Error: Joining threads\n");
			break ;
		}
	}
	i = 0;
	while (i < (var->number_of_philosophers))
	{
		pthread_mutex_destroy(&var->philo[i].l_fork);
		pthread_mutex_destroy(&var->philo[i].mutex_tm_die);
		i++;
	}
	pthread_mutex_destroy(&var->mutex_print);
	pthread_mutex_destroy(&var->mutex_game_ready);
	pthread_mutex_destroy(&var->mutex_game_finished);
	pthread_mutex_destroy(&var->mutex_philos_finished);
	free(var->philo);
	free(var->threads);
}
