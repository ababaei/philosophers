/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:39:53 by ababaei           #+#    #+#             */
/*   Updated: 2021/12/14 18:55:32 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "philo.h"

void check_meal(t_phil *phil)
{
	pthread_mutex_lock(&phil->args->update_meal);
	if (phil->nbmeal == phil->args->nb_eat
			&& phil->args->nb_philo_eat < phil->args->nb_philos)
		phil->args->nb_philo_eat += 1;
	if (phil->args->nb_philo_eat == phil->args->nb_philos)
	{
		pthread_mutex_lock(&phil->args->ending);
		phil->args->end = 1;	
		pthread_mutex_unlock(&phil->args->ending);
	}
	pthread_mutex_unlock(&phil->args->update_meal);
}

int get_killed(t_phil *phil)
{
	long ac_time;

	ac_time = 0;
	pthread_mutex_lock(&phil->args->update_meal);
	if (phil->lastmeal == 0)
		ac_time = get_time() - phil->args->timestamp;
	else
		ac_time = get_time();
	if (ac_time - phil->lastmeal > (long)phil->args->time_die)
	{
		pthread_mutex_unlock(&phil->args->update_meal);
		return (1);
	}
	pthread_mutex_unlock(&phil->args->update_meal);
	return (0);
}

int ate_enough(t_phil *phil)
{
	pthread_mutex_lock(&phil->args->update_meal);
	if (phil->args->nb_philo_eat == phil->args->nb_philos)
	{
		pthread_mutex_unlock(&phil->args->update_meal);
		return (1);
	}
	pthread_mutex_unlock(&phil->args->update_meal);
	return (0);
}

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
		pthread_create(&philos[i].life, NULL, philosopher, &philos[i]);
		i++;
	}
	while (!check_death(&args))
	{
		i = 0;
		while (i < args.nb_philos)
		{
			usleep(100);
			if (get_killed(&philos[i]))
			{
				pthread_mutex_lock(&args.print_mtx);
				write_status("died", &philos[i]);
				pthread_mutex_unlock(&args.print_mtx);
				pthread_mutex_lock(&args.ending);
				args.end = 1;
				pthread_mutex_unlock(&args.ending);
			}
			else if (ate_enough(&philos[i]))
			{
				pthread_mutex_lock(&args.ending);
				args.end = 1;
				pthread_mutex_unlock(&args.ending);
			}
			i++;
		}
	}
	i = 0;
	while (i < args.nb_philos)
	{
		pthread_join(philos[i].life, NULL);
		i++;
	}
	while (i < args.nb_philos)
	{
		pthread_mutex_destroy(&philos[i].l_fork);
		i++;
	}
	pthread_mutex_destroy(&args.print_mtx);
	return (EXIT_SUCCESS);
}
