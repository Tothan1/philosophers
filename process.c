/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 19:03:54 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/03/04 17:24:36 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action(t_philo *philo, int time, char *print)
{
	int lower_time;
	
	lower_time= 0;
	flag_died(philo);
	while(!philo->info->finished && lower_time < time)
	{
		usleep(10 * 1000);
		lower_time += 10;
	}
	// usleep(time* 1000);
	philo_print(philo, print);
}

void	*routine(void *var)
{
	t_philo	*philo;
	int time_think;
	struct timeval start;
	philo = (t_philo *)var;
	gettimeofday(&start, NULL);
	philo->info->start_time = get_time_ms(start);
	philo->last_meal = get_time_ms(start);
	while (!philo->info->finished)
	{
		take_a_fork(philo);
		gettimeofday(&start, NULL);
		philo->last_meal = get_time_ms(start);
		action(philo, philo->info->time_to_sleep, "is sleeping");
		if((philo[philo->id - 1].nb_eat > philo[philo->id - 2].nb_eat || philo[philo->id - 1].nb_eat > philo[philo->id].nb_eat) && philo->id != 1 && philo->id != philo->info->nbr_of_philo -1)
			time_think = 1;
		else if(philo->id == 1 && (philo[philo->id - 1].nb_eat > philo[philo->info->nbr_of_philo - 1].nb_eat || philo[philo->id - 1].nb_eat > philo[philo->id].nb_eat))
			time_think = 1;
		else if(philo->id == philo->info->nbr_of_philo -1 && (philo[philo->id - 1].nb_eat > philo[philo->id - 2].nb_eat || philo[philo->id - 1].nb_eat > philo[0].nb_eat))
			time_think = 1;
		else
			time_think = 0;
		action(philo, time_think, "is thinking");
		flag_died(philo);
	}
	return (NULL);
}

int	take_a_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->self);
		philo_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->neighbor);
		philo_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->neighbor);
		philo_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->self);
		philo_print(philo, "has taken a fork");
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
			// if(global->philosoph[i].nb_eat > global->philosoph[i - 1].nb_eat)
				
			i++;
		}
	}
	return (NULL);
}

int	process(t_glob *var)
{
	int i = 0;
	struct timeval start;
	pthread_mutex_init(&var->info.write, NULL);
	if (var->info.nbr_of_philo == 1)
	{
		gettimeofday(&start, NULL);
		var->philosoph[0].last_meal = get_time_ms(start);
		philo_print(&var->philosoph[0], "has taken a fork");
		usleep(var->info.time_to_die * 1000);
		philo_print(&var->philosoph[0], "is died");
		var->philosoph[0].is_died = 1;
		return (1);
	}
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
