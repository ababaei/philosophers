#include "philo.h"

int init_mutex(t_args *args)
{
	pthread_mutex_init(&args->print_mtx, NULL);
	pthread_mutex_init(&args->ch_stamp, NULL);
	pthread_mutex_init(&args->update_meal, NULL);
	pthread_mutex_init(&args->ending, NULL);
	return (0);
}

int initializer(t_args *args, t_phil **philos)
{
	int i;

	i = 0;
	*philos = malloc(sizeof(t_phil) * args->nb_philos);
	if (*philos == NULL)
		return (EXIT_FAILURE);
	while (i < args->nb_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].nbmeal = 0;
		(*philos)[i].lastmeal = 0;
		(*philos)[i].args = args;
		(*philos)[i].r_fork = NULL;
		if (pthread_mutex_init(&(*philos)[i].l_fork, NULL))
			return (EXIT_FAILURE);
		if (i == args->nb_philos - 1)
			(*philos)[args->nb_philos - 1].r_fork = &(*philos)[0].l_fork;
		else
			(*philos)[i].r_fork = &(*philos)[i + 1].l_fork;
		i++;
	}
	init_mutex(args);
	return (0);
}
