/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ababaei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 11:07:18 by ababaei           #+#    #+#             */
/*   Updated: 2021/12/15 11:08:38 by ababaei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fill_input(char *argv, int *to_fill)
{
	char	*end;

	*to_fill = ft_strtol(argv, &end, 10);
	if (end[0] || *to_fill > INT_MAX || *to_fill <= 0)
		return (-1);
	return (0);
}

int	parser(int argc, char **argv, t_args *args)
{
	if (argc == 5 || argc == 6)
	{
		if (fill_input(argv[1], &args->nb_philos) \
			|| fill_input(argv[2], &args->time_die) \
			|| fill_input(argv[3], &args->time_eat) \
			|| fill_input(argv[4], &args->time_sleep))
			return (-1);
		if (argc == 6)
		{
			if (fill_input(argv[5], &args->nb_eat))
				return (-1);
			return (0);
		}
		args->nb_eat = -1;
		return (0);
	}
	return (-1);
}
