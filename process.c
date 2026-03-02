/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 19:03:54 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/03/02 20:03:23 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action(t_philo *philo, int time, char *print)
{
	int lower_time;
	lower_time = 10;
	while(!philo->info->finished && lower_time < time)
	{
		usleep(lower_time * 1000);
		lower_time += 10;
	}
		philo_print(philo, time, print);
}

void	*routine(void *var)
{
	t_philo	*philo;

	struct timeval start, end, end2;
	philo = (t_philo *)var;
	while (!philo->info->finished)
	{
		gettimeofday(&start, NULL);
		take_a_fork(philo);
		gettimeofday(&end, NULL);
		/* if (((end.tv_usec - start.tv_usec) * 1000) > philo->info->time_to_eat)
		{
			philo_print(philo, 0, "is died");
			philo->is_died = 1;
		} */
		action(philo, philo->info->time_to_sleep, "is sleeping");
		action(philo, 50, "is thinking");
		gettimeofday(&end2, NULL);
		if (((end2.tv_usec - start.tv_usec) * 1000) > philo->info->time_to_die)
		{
			philo_print(philo, 0, "is died");
			philo->is_died = 1;
			philo->info->finished = 1;
		}
	}
	return (NULL);
}

int	take_a_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->self);
		philo_print(philo, 0, "has taken a fork");
		pthread_mutex_lock(philo->neighbor);
		philo_print(philo, 0, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->neighbor);
		philo_print(philo, 0, "has taken a fork");
		pthread_mutex_lock(&philo->self);
		philo_print(philo, 0, "has taken a fork");
	}
	action(philo, philo->info->time_to_eat, "is eating");
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->self);
	pthread_mutex_unlock(philo->neighbor);
	return (1);
}
void	*monitor(void * var)
{
	t_glob	*global;

	global = (t_glob*) var;
	int i;
	while (!global->info.finished)
	{
		i = 0;
		while (i < global->info.nbr_of_philo)
		{
			if(global->philosoph[i].nb_eat == global->info.nbr_must_eat  && global->info.nbr_must_eat != -1)
				global->info.finished = 1;
			if(global->philosoph[i].is_died == 1)
				global->info.finished = 1;
			i++;
		}
	}
	return (NULL);
}

int	process(t_glob *var)
{
	int i = 0;
	if (var->info.nbr_of_philo == 1)
	{
		philo_print(&var->philosoph[0], 0, "has taken a fork");
		usleep(var->info.time_to_die * 1000);
		philo_print(&var->philosoph[0], 0, "is died");
		var->philosoph[0].is_died = 1;
		return (1);
	}
	pthread_mutex_init(&var->info.write, NULL);
	while (i < var->info.nbr_of_philo)
	{
		pthread_mutex_init(&var->philosoph[i].self, NULL);
		if (pthread_create(&var->philosoph[i].p, NULL, &routine,
				&var->philosoph[i]) != 0)
			return (2);
		i++;
	}
	if (pthread_create(&var->died.p, NULL, &monitor, var) != 0)
		return (2);
	return (1);
}