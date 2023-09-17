/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 11:48:49 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/17 14:03:10 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print_line(t_philo *aux, char *s)
{
	int		i;
	int		game_finished;

	i = ft_time_passed(aux->var->tm_start);
	pthread_mutex_lock(&aux->var->mutex_print);
	pthread_mutex_lock(&aux->var->mutex_game_finished);
	game_finished = aux->var->game_finished;
	pthread_mutex_unlock(&aux->var->mutex_game_finished);
	if (game_finished != 1)
		printf("%d %d %s\n", i, aux->philo_nbr + 1, s);
	pthread_mutex_unlock(&aux->var->mutex_print);
}

int	main(int argc, char **argv)
{
	t_var	var;

	if (argc != 5 && argc != 6)
	{
		printf("Please pass at least 4 arguments:\n");
		printf("1. number_of_philosophers\n2. time_to_die\n");
		printf("3. time_to_eat\n4. time_to_sleep\n");
		printf("5. number_of_times_each_philo_must_eat (optional)");
		return (1);
	}
	if (ft_args_check(argc, argv) == 1)
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	var_init(&var, argv);
	ft_sleep(1, &var);
	pthread_mutex_unlock(&var.mutex_game_ready);
	gettimeofday(&var.tm_start, NULL);
	monitor(&var);
	ft_finish(&var);
	return (0);
}
