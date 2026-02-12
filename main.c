/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:42:25 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/12 10:25:13 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

void	free(t_glob var)
{
	exit(1);
}


t_philo	**recover_map(t_glob var)
{
	t_philo	*philosoph;
	int		i;

	philosoph = malloc(sizeof(t_philo *) * (var.number_of_philosophers - 1));
	i = 0;
	while (i < (var.number_of_philosophers - 1))
	{
		philosoph[i].id = i;
		philosoph[i].nb_fork = 0;
		i++;
	}
	return (philosoph);
}

void	*routine (t_glob var)
{
	
}

t_glob	process(t_glob var, int i)
{
	if (pthread_create(var.philosoph[i].p, NULL, &routine, &var.philosoph[i]) != 0)
		exit (2);
	if (pthread_join(var.philosoph[i].p, NULL) != 0)
		exit (2);
	return (var);
}


int	main(int ac, char **av)
{
	t_glob var;
	pthread_mutex_t mutex;
	int i;
	if (ac == 5 || ac == 6)
	{
		pthread_mutex_init(&mutex, NULL);
		var.number_of_philosophers = av[1];
		var.time_to_die = av[2];
		var.time_to_eat = av[3];
		var.time_to_sleep = av[4];
		if (ac == 6)
		var.number_of_times_each_philosopher_must_eat = av[5];
		else
		var.number_of_times_each_philosopher_must_eat = -1;
		var.philosoph = recover_map(var);
		while (i < var.number_of_times_each_philosopher_must_eat
			|| var.number_of_times_each_philosopher_must_eat == 1)
			{
				var = process(var, i);
				i++;
			}
			pthread_mutex_destroy(&mutex);
		}
	else
		return (2);
}