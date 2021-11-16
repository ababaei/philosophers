#include "philo.h"

int initializer(t_args *args, t_phil **philos)
{
	int i;

	i = 0;
	*philos = malloc(sizeof(t_phil) * args->nb_philos);
	if (*philos == NULL)
		return (EXIT_FAILURE);
	while (i < args->nb_philos)
	{
		(*philos)[i].id = i;
		(*philos)[i].args = args;
		(*philos)[i].r_fork = NULL;
		if (pthread_mutex_init(&(*philos)[i].l_fork, NULL))
			return (EXIT_FAILURE);
		if (i == args->nb_philos - 1)
			(*philos)[0].r_fork = &(*philos)[i].l_fork;
		else
			(*philos)[i].r_fork = &(*philos)[i + 1].l_fork;
		i++;
	}
	i = 0;
	while (i < args->nb_philos)
	{
		printf("id = %d\n", (*philos)[i].id);
		i++;
	}
	return (0);
}
