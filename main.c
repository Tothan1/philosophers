/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:42:25 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/11 11:30:46 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

t_philosoph	**recover_map(t_glob var)
{
	t_philosoph	*philosoph;
	int		i;

	philosoph = malloc(sizeof(t_philosoph *) * (var.number_of_philosophers - 1));
	i = 0;
	while (i < (var.number_of_philosophers - 1))
	{
		philosoph[i].id = i;
		philosoph[i].nb_fork = 0;
		i++;
	}
	return (philosoph);
}

int	main(int ac, char **av)
{
	t_glob var;
	int i;
	if (ac == 5 || ac == 6)
	{
		var.number_of_philosophers = av[1];
		var.time_to_die = av[2];
		var.time_to_eat = av[3];
		var.time_to_sleep = av[4];
		if (ac == 6)
			var.number_of_times_each_philosopher_must_eat = av[5];
		else
			var.number_of_times_each_philosopher_must_eat = -1;
		var.philosoph = recover_map(var);
		if(pthread_create()!=0)
			return (2);
		while (i < var.number_of_times_each_philosopher_must_eat)
		{
			
			i++;
		}
		
	}
	else
		return (2);
}