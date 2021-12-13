#include "philo.h"

void	eating(t_phil *phil)
{
	pthread_mutex_lock(&phil->l_fork);
	pthread_mutex_lock(&phil->args->print_mtx);
	write_status("has taken a fork", phil);
	pthread_mutex_unlock(&phil->args->print_mtx);
	pthread_mutex_lock(phil->r_fork);
	pthread_mutex_lock(&phil->args->print_mtx);
	write_status("has taken a fork", phil);
	pthread_mutex_unlock(&phil->args->print_mtx);
	pthread_mutex_lock(&phil->args->print_mtx);
	write_status("is eating", phil);
	pthread_mutex_unlock(&phil->args->print_mtx);
	pthread_mutex_lock(&phil->args->update_meal);
	phil->lastmeal = get_time();
	pthread_mutex_unlock(&phil->args->update_meal);
	ft_usleep(phil->args->time_eat);
	pthread_mutex_unlock(phil->r_fork);
	pthread_mutex_unlock(&phil->l_fork);
}

void	sleeping(t_phil *phil)
{
	pthread_mutex_lock(&phil->args->print_mtx);
	write_status("is sleeping", phil);
	pthread_mutex_unlock(&phil->args->print_mtx);
	ft_usleep(phil->args->time_sleep);
	pthread_mutex_lock(&phil->args->print_mtx);
	write_status("is thinking", phil);
	pthread_mutex_unlock(&phil->args->print_mtx);
}

void	*philosopher(void *data)
{
	t_phil	*phil;

	phil = data;
	if (phil->id % 2 == 1)
		ft_usleep(10);
	while (!check_death(phil->args))
	{
		eating(phil);
		sleeping(phil);
	}
	return (NULL);
}
