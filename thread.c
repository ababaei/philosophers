#include "philo.h"

void	eating(t_phil *phil)
{
	pthread_mutex_lock(phil->r_fork);
	pthread_mutex_lock(phil->args->print_mtx);
	printf("%ld %d has taken a fork\n", get_timestamp(), phil->id);
	pthread_mutex_unlock(phil->args->print_mtx);
	pthread_mutex_lock(&phil->l_fork);
	pthread_mutex_lock(phil->args->print_mtx);
	printf("%ld %d has taken a fork\n", get_timestamp(), phil->id);
	pthread_mutex_unlock(phil->args->print_mtx);
	pthread_mutex_lock(phil->args->print_mtx);
	printf("%ld %d is eating\n", get_timestamp(), phil->id);
	pthread_mutex_unlock(phil->args->print_mtx);
	ft_usleep(phil->args->time_eat);
	pthread_mutex_unlock(phil->r_fork);
	pthread_mutex_unlock(&phil->l_fork);
	phil->has_eaten = 1;
}

void	dying(void *data)
{
	t_phil	*phil;
	
	phil = data;
	ft_usleep(phil->args->time_die);
	pthread_mutex_lock(&phil->eating);
	if (phil->has_eaten == 0)
		phil->is_dead = 1;
	
}

void	philosopher(void *data)
{
	t_phil	*phil;

	phil = data;
	pthread_mutex_lock(&phil->eating);
	eating(phil);
	pthread_mutex_unlock(&phil->eating);
	// ft_usleep(50 * phil->id); //// PUT IT IN STARTER.C 
}
