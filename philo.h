/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:16:37 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/16 20:24:52 by mmoramov         ###   ########.fr       */
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

};

struct s_var
{
	int				number_of_philosophers;
	int				tm_die;
	int				tm_eat;
	int				tm_sleep;
	int				nr_must_eat;
	struct timeval	tm_start;
	pthread_mutex_t	print;
	pthread_mutex_t	ready;
	int				finish;
	struct s_philo	*philo;
	pthread_t		*threads;
};

int		ft_get_time_ms(void);
int	ft_sleep(int millisec, t_var *var);
int		ft_atoi(const char *str);
int		ft_args_check(int argc, char **argv);
int	ft_time_passed(t_var *var);
void* routine(void *arg);

void var_init(t_var *var, char **argv);
void philos_init(t_var *var);
int threads_init(t_var *var);

#endif
