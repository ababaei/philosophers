/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:39:53 by ababaei           #+#    #+#             */
/*   Updated: 2021/11/19 14:43:48 by ababaei          ###   ########.fr       */
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
	if (parser(argc, argv, &args))
		return (EXIT_FAILURE);
	if (initializer(&args, &philos))
		return (EXIT_FAILURE);
	while (i < args.nb_philos)
	{
		printf("lf = %p\n", &philos[i].l_fork);
		printf("rf = %p\n", philos[i].r_fork);
		printf("id = %d\n", philos[i].id);
		i++;
	}
	i = 0;
//	pthread_create(&philos[0].life, NULL, philosopher, &philos[i]);
//	pthread_join(philos[0].life, NULL);

	while (i < args.nb_philos)
	{
		pthread_create(&philos[i].life, NULL, philosopher, &philos[i]);
		i++;
	}
	i = 0;
	while (i < args.nb_philos)
	{
		pthread_join(philos[i].life, NULL);
		i++;
	}
	return (EXIT_SUCCESS);
}
