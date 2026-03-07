/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 19:03:54 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/03/07 18:27:49 by tle-rhun         ###   ########.fr       */
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
	int		time_think;

	time_think = 0;
	philo = (t_philo *)var;
	philo->last_meal = get_time_ms();
	if (philo->id % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(&philo->info->died);
	pthread_mutex_lock(&philo->eat);
	while (!philo->info->finished && (philo->info->nbr_must_eat == -1
			|| philo->nb_eat < philo->info->nbr_must_eat))
	{
		pthread_mutex_unlock(&philo->info->died);
		pthread_mutex_unlock(&philo->eat);
		take_a_fork(philo);
		action(philo, philo->info->time_to_sleep, "is sleeping");
		action(philo, 1, "is thinking");
		pthread_mutex_lock(&philo->info->died);
		pthread_mutex_lock(&philo->eat);
	}
	pthread_mutex_unlock(&philo->eat);
	pthread_mutex_unlock(&philo->info->died);
	return (NULL);
}

int	take_a_fork(t_philo *philo)
{
	if (!philo->info->finished)
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
	}
	action(philo, philo->info->time_to_eat, "is eating");
	philo->last_meal = get_time_ms();
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
	int		i;

	global = (t_glob *)var;
	while (!global->info.finished)
	{
		i = 0;
		nb_philo_must_eat = 0;
		while (i < global->info.nbr_of_philo)
		{
			pthread_mutex_lock(&global->philosoph[i].eat);
			if (global->philosoph[i].nb_eat == global->info.nbr_must_eat
				&& global->info.nbr_must_eat != -1)
				nb_philo_must_eat++;
			pthread_mutex_unlock(&global->philosoph[i].eat);
			i++;
		}
		pthread_mutex_lock(&global->info.died);
		if (nb_philo_must_eat == global->info.nbr_of_philo
			&& global->info.nbr_must_eat != -1)
			global->info.finished = 1;
		pthread_mutex_unlock(&global->info.died);
		usleep(1000);
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
	if (pthread_create(&var->died.p, NULL, &monitor, var) != 0)
		return (2);
	return (1);
}
