/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <ababaei@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:39:53 by ababaei           #+#    #+#             */
/*   Updated: 2021/12/17 15:46:58 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "philo.h"

int	get_killed(t_phil *phil)
{
	long	ac_time;

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

void	diner(t_args *args, t_phil **philos)
{
	int	i;

	i = -1;
	while (++i < args->nb_philos)
		pthread_create(&(*philos)[i].life, NULL, philosopher, &(*philos)[i]);
	while (!check_death(args))
	{
		i = -1;
		while (++i < args->nb_philos)
		{
			usleep(100);
			if (get_killed(&(*philos)[i]))
			{
				pthread_mutex_lock(&args->print_mtx);
				write_status("died", &(*philos)[i]);
				pthread_mutex_unlock(&args->print_mtx);
				pthread_mutex_lock(&args->ending);
				args->end = 1;
				pthread_mutex_unlock(&args->ending);
			}
		}
	}
}

void	ender(t_args *args, t_phil **philos)
{
	int	i;

	i = -1;
	if (args->nb_philos == 1)
		pthread_detach((*philos)[0].life);
	while (++i < args->nb_philos)
		pthread_join((*philos)[i].life, NULL);
	i = -1;
	while (++i < args->nb_philos)
		pthread_mutex_destroy(&(*philos)[i].l_fork);
	pthread_mutex_destroy(&args->print_mtx);
	free(*philos);
}

int	main(int argc, char **argv)
{
	t_args	args;
	t_phil	*philos;

	args.end = 0;
	if (parser(argc, argv, &args) || initializer(&args, &philos))
		return (EXIT_FAILURE);
	diner(&args, &philos);
	ender(&args, &philos);
	return (EXIT_SUCCESS);
}
