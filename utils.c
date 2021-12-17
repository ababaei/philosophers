/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:29:10 by ababaei           #+#    #+#             */
/*   Updated: 2021/12/17 15:05:37 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_args *args)
{
	pthread_mutex_lock(&args->ending);
	if (args->end)
	{
		pthread_mutex_unlock(&args->ending);
		return (1);
	}
	pthread_mutex_unlock(&args->ending);
	return (0);
}

long	get_time(void)
{
	long			time;
	struct timeval	tv;

	time = 0;
	if (gettimeofday(&tv, NULL))
		return (-1);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

long	ft_usleep(long usec)
{
	long long	start;

	start = get_time();
	while (get_time() - start < usec)
		usleep(100);
	return (start);
}

void	write_status(char *str, t_phil *phil)
{
	long	time;

	time = 0;
	time = get_time() - phil->args->timestamp;
	if (time >= 0 && time <= INT_MAX && !check_death(phil->args))
		printf("%ld %d %s\n", time, phil->id, str);
}
