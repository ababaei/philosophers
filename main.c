/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:39:53 by ababaei           #+#    #+#             */
/*   Updated: 2021/12/03 19:22:41 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "philo.h"

int	main(int argc, char **argv)
{
	t_args args;
	t_phil *philos;
	int i;

	i = 0;
	args.end = 0;
	if (parser(argc, argv, &args))
		return (EXIT_FAILURE);
	if (initializer(&args, &philos))
		return (EXIT_FAILURE);
	while (i < args.nb_philos)
	{
		ft_usleep(5 * i); 
		pthread_create(&philos[i].life, NULL, philosopher, &philos[i]);
		i++;
	}
	while (!args.end)
	{
		i = 0;
		while (i < args.nb_philos)
		{
			if (get_timestamp() - philos[i].lastmeal > args.time_die)
			{
				pthread_mutex_lock(&args.print_mtx);
				printf("%ld %d died\n", get_timestamp(), philos[i].id);
				pthread_mutex_unlock(&args.print_mtx);
				args.end = 1;		
			}	
			i++;
		}
	}
	while (i < args.nb_philos)
	{
		pthread_join(philos[i].life, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}
