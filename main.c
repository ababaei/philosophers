/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:39:53 by ababaei           #+#    #+#             */
/*   Updated: 2021/11/18 16:07:06 by ababaei          ###   ########.fr       */
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
		printf("TOTO\n");
		if (!pthread_create(&philos[i].life, NULL, philosopher, &philos[i]))
			return (-1);
		i++;
	}
	i = 0;
	while (i < args.nb_philos)
	{
		if (!pthread_join(philos[i].life, NULL))
			return (-1);
		i++;
	}
	return (EXIT_SUCCESS);
}
