#include "philo.h"

int initializer(t_args *args, t_phil **philos)
{
	int i;

	i = 0;
	*philos = malloc(sizeof(t_phil) * args->nb_philos);
	while (i < args->nb_philos)
	{
		(*philos)[i].id = i;
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
