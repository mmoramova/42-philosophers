/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 11:48:49 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/17 13:08:41 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_line(t_philo *aux, char *s)
{
	int	i;
	int		game_finished;


	i = ft_time_passed(aux->var->tm_start);
	pthread_mutex_lock(&aux->var->print);

	pthread_mutex_lock(&aux->var->finished);
	game_finished = aux->var->game_finished;
	pthread_mutex_unlock(&aux->var->finished);

	if (game_finished != 1)
		printf("%d %d %s\n", i, aux->philo_nbr + 1, s);
	pthread_mutex_unlock(&aux->var->print);
}

void *routine(void *arg)
{
	t_philo	*aux;
	int		i;
	int		game_finished;

	aux = (t_philo *)arg;
	pthread_mutex_lock(&aux->var->ready);
	pthread_mutex_unlock(&aux->var->ready);
	if ((aux->philo_nbr) % 2 == 1)
	{
		ft_sleep(1, aux->var);   //dr TIME2
		pthread_mutex_lock(&aux->var->ready);
		pthread_mutex_unlock(&aux->var->ready);
	}
	i = 0;
	game_finished = 0;
	while (game_finished != 1) //dr FINISHED
	{
		if (aux->var->number_of_philosophers == 1)
		{
			pthread_mutex_lock(&aux->var->finished);
			game_finished = aux->var->game_finished;
			pthread_mutex_unlock(&aux->var->finished);
			continue;
		}

		pthread_mutex_lock(&aux->l_fork);
		pthread_mutex_lock(aux->r_fork);
		ft_print_line(aux, FORK);
		ft_print_line(aux, FORK);

		pthread_mutex_lock(&aux->mutex_tm_die);
		aux->tm_die = ft_time_passed(aux->var->tm_start) + aux->var->tm_die; //dr  TIME1
		pthread_mutex_unlock(&aux->mutex_tm_die);

		ft_print_line(aux, EAT);
		ft_sleep(aux->var->tm_eat, aux->var); //dr TIME2
		if (aux->var->nr_must_eat > 0 && aux->eaten_times_left > 0)
		{
			aux->eaten_times_left--; //dr EATEN TIMES
			if (aux->eaten_times_left == 0)
			{
				pthread_mutex_lock(&aux->var->philo_finished);
				aux->var->philos_finished++;
				pthread_mutex_unlock(&aux->var->philo_finished);
			}

		}
		pthread_mutex_unlock(&aux->l_fork);
		pthread_mutex_unlock(aux->r_fork);
		ft_print_line(aux, SLEEP);
		ft_sleep(aux->var->tm_sleep, aux->var); //dr  TIME2
		ft_print_line(aux, THINK);
		pthread_mutex_lock(&aux->var->finished);
		game_finished = aux->var->game_finished;
		pthread_mutex_unlock(&aux->var->finished);
	}
	return (void*) 0;
}

void monitor(t_var *var)
{
	int		i;
	int		philo_finished_eaten;
	int		philo_tm_die;

	i = 0;
	philo_finished_eaten = 0;
	while (i < var->number_of_philosophers)
	{
		pthread_mutex_lock(&var->philo[i].mutex_tm_die);
		philo_tm_die = var->philo[i].tm_die;
		pthread_mutex_unlock(&var->philo[i].mutex_tm_die);
		if (ft_time_passed(var->tm_start) >= philo_tm_die) //dr TIME1
		{
			ft_print_line(&var->philo[i], DIE);
			pthread_mutex_lock(&var->finished);
			var->game_finished = 1; //dr FINISHED
			pthread_mutex_unlock(&var->finished);

			break;
		}
		if (var->nr_must_eat > 0)
		{
			pthread_mutex_lock(&var->philo_finished);
				philo_finished_eaten = var->philos_finished;
			pthread_mutex_unlock(&var->philo_finished);
			if (philo_finished_eaten == var->number_of_philosophers)
			{
				pthread_mutex_lock(&var->finished);
				var->game_finished = 1; //dr FINISHED
				pthread_mutex_unlock(&var->finished);
				break;
			}
		i++;
		if (i == var->number_of_philosophers)
			{
				i = 0;
			}
		}
		usleep(100);
	}
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
			break;
		}
	}
	i = 0;
	while (i < (var->number_of_philosophers))
	{
		pthread_mutex_destroy(&var->philo[i].l_fork);
		pthread_mutex_destroy(&var->philo[i].mutex_tm_die);
		i++;
	}
	pthread_mutex_destroy(&var->print);
	pthread_mutex_destroy(&var->ready);
	pthread_mutex_destroy(&var->finished);
	pthread_mutex_destroy(&var->philo_finished);
	free(var->philo);
	free(var->threads);
}

int	main(int argc, char **argv)
{
	t_var	var;

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
	ft_finish(&var);
	return (0);
}
