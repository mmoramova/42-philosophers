/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:16:37 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/17 13:05:14 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
#include <stdlib.h>

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

typedef struct s_var t_var;
typedef struct s_philo t_philo;

struct s_philo
{
	int					philo_nbr;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		l_fork;
	int					eaten_times_left;
	int					tm_die;
	struct s_var		*var;
	pthread_mutex_t		mutex_tm_die;
};

struct s_var
{
	int				number_of_philosophers;
	int				tm_die;
	int				tm_eat;
	int				tm_sleep;
	int				nr_must_eat;
	int				game_finished;
	int				philos_finished;
	struct timeval	tm_start;
	struct s_philo	*philo;
	pthread_t		*threads;
	pthread_mutex_t	print;
	pthread_mutex_t	ready;
	pthread_mutex_t	finished;
	pthread_mutex_t	philo_finished;
};

int	ft_sleep(int millisec, t_var *var);
int		ft_atoi(const char *str);
int		ft_args_check(int argc, char **argv);
void* routine(void *arg);

void var_init(t_var *var, char **argv);
void philos_init(t_var *var);
int	ft_time_passed(struct timeval tm_start);
int threads_init(t_var *var);

#endif
