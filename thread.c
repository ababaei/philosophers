#include "philo.h"

void	eating(t_phil *phil)
{
	pthread_mutex_lock(phil->r_fork);
	pthread_mutex_lock(&phil->args->print_mtx);
	printf("%ld %d has taken a fork\n", get_timestamp(), phil->id);
	pthread_mutex_unlock(&phil->args->print_mtx);
	pthread_mutex_lock(&phil->l_fork);
	pthread_mutex_lock(&phil->args->print_mtx);
	printf("%ld %d has taken a fork\n", get_timestamp(), phil->id);
	pthread_mutex_unlock(&phil->args->print_mtx);
	pthread_mutex_lock(&phil->args->print_mtx);
	printf("%ld %d is eating\n", get_timestamp(), phil->id);
	pthread_mutex_unlock(&phil->args->print_mtx);
	phil->lastmeal = get_timestamp();
	ft_usleep(phil->args->time_eat);
	pthread_mutex_unlock(&phil->l_fork);
	pthread_mutex_unlock(phil->r_fork);
}

void	sleeping(t_phil *phil)
{
	pthread_mutex_lock(&phil->args->print_mtx);
	printf("%ld %d is sleeping\n", get_timestamp(), phil->id);
	pthread_mutex_unlock(&phil->args->print_mtx);
	ft_usleep(phil->args->time_sleep);
	pthread_mutex_lock(&phil->args->print_mtx);
	printf("%ld %d is thinking\n", get_timestamp(), phil->id);
	pthread_mutex_unlock(&phil->args->print_mtx);
}

void	*philosopher(void *data)
{
	t_phil	*phil;

	phil = data;
	eating(phil);
	sleeping(phil);
//	dying(phil);
	return (NULL);
}
