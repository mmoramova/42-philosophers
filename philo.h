/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmoramov <mmoramov@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 13:16:37 by mmoramov          #+#    #+#             */
/*   Updated: 2023/09/09 15:11:36 by mmoramov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
#include <stdlib.h>

# define FORK "has taken a fork";
# define EAT "is eating";
# define SLEEP "is sleeping";
# define THINK "is thinking";
# define DIE "died";

typedef struct s_philo
{
	int					philo_nbr;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		l_fork;
	int					eaten_times;
	int					tm_die;

}	t_philo;

typedef struct s_var
{
	int				number_of_philosophers;
	int				tm_die;
	int				tm_eat;
	int				tm_sleep;
	int				nr_must_eat;
	struct s_philo	*philo;
}	t_var;

int		ft_get_time_ms(void);
int		ft_sleep(int millisec);
int		ft_atoi(const char *str);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ft_args_check(int argc, char **argv);

#endif
