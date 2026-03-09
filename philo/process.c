/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 19:03:54 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/03/09 18:35:36 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	action(t_philo *philo, int time, char *print)
{
	long	before;

	philo_print(philo, print);
	before = get_time_ms();
	while ((get_time_ms() - before) < time && flag_died(philo))
		usleep(500);
}

void	*routine(void *var)
{
	t_philo	*philo;

	philo = (t_philo *)var;
	if (philo->id % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->meal);
	pthread_mutex_lock(&philo->eat);
	while (flag_died(philo) && (philo->info->nbr_must_eat == -1
			|| philo->nb_eat < philo->info->nbr_must_eat))
	{
		pthread_mutex_unlock(&philo->eat);
		take_a_fork(philo);
		action(philo, philo->info->time_to_sleep, "is sleeping");
		action(philo, 1, "is thinking");
		pthread_mutex_lock(&philo->eat);
	}
	pthread_mutex_unlock(&philo->eat);
	return (NULL);
}

int	take_a_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->neighbor);
		philo_print(philo, "has taken a fork");
		pthread_mutex_lock(&philo->self);
		philo_print(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->self);
		philo_print(philo, "has taken a fork");
		pthread_mutex_lock(philo->neighbor);
		philo_print(philo, "has taken a fork");
	}
	action(philo, philo->info->time_to_eat, "is eating");
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->meal);
	pthread_mutex_lock(&philo->eat);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->eat);
	pthread_mutex_unlock(&philo->self);
	pthread_mutex_unlock(philo->neighbor);
	return (1);
}

void	*monitor(void *var)
{
	t_glob	*global;
	int		nb_philo_must_eat;

	global = (t_glob *)var;
	while (flag_died(global->philosoph))
	{
		nb_philo_must_eat = monitorv2(global, 0, 0);
		if (nb_philo_must_eat == -1)
			return (0);
		if (nb_philo_must_eat == global->info.nbr_of_philo
			&& global->info.nbr_must_eat != -1)
			global->info.finished = 1;
	}
	return (NULL);
}

int	process(t_glob *var)
{
	int	i;

	i = 0;
	pthread_mutex_init(&var->info.write, NULL);
	pthread_mutex_init(&var->info.died, NULL);
	var->info.start_time = get_time_ms();
	if (var->info.nbr_of_philo == 1)
	{
		var->philosoph[0].last_meal = get_time_ms();
		philo_print(&var->philosoph[0], "has taken a fork");
		usleep(var->info.time_to_die * 1000);
		philo_print(&var->philosoph[0], "died");
		return (1);
	}
	while (i < var->info.nbr_of_philo)
	{
		if (pthread_create(&var->philosoph[i].p, NULL, &routine,
				&var->philosoph[i]) != 0)
			return (2);
		i++;
	}
	if (pthread_create(&var->p, NULL, &monitor, var) != 0)
		return (2);
	return (1);
}
