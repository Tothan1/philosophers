/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 19:03:54 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/16 19:26:18 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	action(t_philo philo, int time, char * print)
{
	check_is_died(philo.info);
	if(check_is_died(philo.info)==0)
		return;
	usleep(time * 1000);
	philo_print(philo, time, print);
}
void	*routine (void* var)
{
	t_philo *philo;
	struct timeval start, end;
	philo = (t_philo *)var;
	check_is_died(philo->info);
	gettimeofday(&start, NULL);
	take_a_fork(*philo);
	action(*philo, philo->info.time_to_eat, "is eating");
	philo->nb_eat++;
	action(*philo, philo->info.time_to_sleep, "is sleeping");
	action(*philo, 1 , "is thinking");
	gettimeofday(&end, NULL);
	if(((end.tv_usec - start.tv_usec) * 1000)< philo->info.time_to_die)
	{
		philo_print(*philo, 0, "died");
		philo->info.is_died = 1;
	}
	return (NULL);
}

void	take_a_fork(t_philo philo)
{
	check_is_died(philo.info);
	pthread_mutex_lock(&philo.self);
	philo_print(philo, 0,"has taken a fork");
	pthread_mutex_unlock(&philo.self);
	check_is_died(philo.info);
	pthread_mutex_lock(&philo.neighbor);
	philo_print(philo, 0,"has taken a fork");
	pthread_mutex_unlock(&philo.neighbor);
}
int	process(t_glob *var)
{
	int i = 0;
	while (i < var->info.number_of_philosophers)
	{
		if (pthread_create(&var->philosoph[i].p, NULL, &routine, &var->philosoph[i]) != 0)
			return (2);
		if (pthread_join(var->philosoph[i].p, NULL) != 0)
			return (2);
		i++;
	}
	return (1);
}