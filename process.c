/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 19:03:54 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/28 19:22:56 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	action(t_philo *philo, int time, char * print)
{
	if(philo->info->is_died == 1)
		return;
	usleep(time * 1000);
	philo_print(philo, time, print);
}
void	*routine (void* var)
{
	t_philo *philo;
	struct timeval start, end;
	philo = (t_philo *)var;
	gettimeofday(&start, NULL);
	if(philo->info->is_died == 1)
		return(NULL);
	take_a_fork(philo);
	action(philo, philo->info->time_to_sleep, "is sleeping");
	action(philo, 100 , "is thinking");
	gettimeofday(&end, NULL);
	if(((end.tv_usec - start.tv_usec) * 1000)< philo->info->time_to_die)
	{
		// philo_print(&&philo, 0, "is died");
		philo->info->is_died = 1;
	}
	return (NULL);
}


int	take_a_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->self);
	philo_print(philo, 0,"has taken a fork");
	if(philo->info->is_died == 1)
		return(2);
	pthread_mutex_lock(&philo->neighbor);
	philo_print(philo, 0,"has taken a fork");
	action(philo, philo->info->time_to_eat, "is eating");
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->self);
	pthread_mutex_unlock(&philo->neighbor);
	// udpate de last_meal time
	return(1);
}
int	process(t_glob *var)
{
	int i = 0;
	while (i < var->info.nbr_of_philo)
	{
		if (pthread_create(&var->philosoph[i].p, NULL, &routine, &var->philosoph[i]) != 0)
			return (2);
		i++;
	}
	printf ("test");
	return (1);
}