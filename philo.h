/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:56:00 by ababaei           #+#    #+#             */
/*   Updated: 2021/12/17 14:09:19 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

typedef struct s_args
{
	int				nb_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_eat;
	int				nb_philo_eat;

	long			timestamp;
	int				end;

	pthread_mutex_t	print_mtx;
	pthread_mutex_t	ch_stamp;
	pthread_mutex_t	update_meal;
	pthread_mutex_t	ending;
}			t_args;

typedef struct s_phil
{
	int				id;
	long			lastmeal;
	int				nbmeal;
	int				eatenough;

	pthread_t		life;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	l_fork;

	t_args			*args;
}			t_phil;

int		parser(int argc, char **argv, t_args *args);
int		initializer(t_args *args, t_phil **philos);
void	*philosopher(void *data);

long	ft_strtol(char *nptr, char **endptr, int base);
long	get_time(void);
long	ft_usleep(long usec);
void	write_status(char *str, t_phil *phil);
int		check_death(t_args *args);

#endif
