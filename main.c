/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:39:53 by ababaei           #+#    #+#             */
/*   Updated: 2021/11/16 18:38:42 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "philo.h"

long	get_timestamp(void)
{
	static long start = 0;
	long 		time;
	struct timeval tv;

	time = 0;
	if (gettimeofday(&tv, NULL))
		return (-1);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (start == 0)
		 start = time; 
	time = time - start;
	return (time);
}

int	ft_usleep(long usec)
{
	long	start;
	long	time;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	time = 0;	
	while (time < usec / 1000)
	{
		time = gettimeofday() - start;
		printf("time = %ld\n", time);
	}
	return (time);
}

int	main(int argc, char **argv)
{
	t_args args;
	t_phil *philos;

	if (parser(argc, argv, &args))
		return (EXIT_FAILURE);
	if (initializer(&args, &philos))
		return (EXIT_FAILURE);
	printf("%ld\n", get_timestamp());
	ft_usleep(5000);	
	//usleep(5000000);
	printf("%ld\n", get_timestamp());
}
