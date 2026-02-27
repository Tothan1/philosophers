/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 19:03:54 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/27 19:29:06 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	action(t_philo **philo, int time, char * print)
{
	if(check_is_died((*philo)->info)==0)
		return;
	usleep(time * 1000);
	philo_print(&philo, time, print);
}
void	*routine (void* var)
{
	t_philo *philo;
	struct timeval start, end;
	philo = (t_philo *)var;
	check_is_died(philo->info);
	gettimeofday(&start, NULL);
	take_a_fork(&philo);

	action(&philo, philo->info->time_to_eat, "is eating");
	philo->nb_eat++;
	action(&philo, philo->info->time_to_sleep, "is sleeping");
	action(&philo, 100 , "is thinking");
	gettimeofday(&end, NULL);
	if(((end.tv_usec - start.tv_usec) * 1000)< philo->info->time_to_die)
	{
		// philo_print(&&philo, 0, "is died");
		philo->info->is_died = 1;
	}
	return (NULL);
}


int	take_a_fork(t_philo **philo)
{

	if((*philo)->info->is_died == 1)
		return(2);
	pthread_mutex_lock(&(*philo)->self);
	philo_print(&philo, 0,"has taken a fork");
	pthread_mutex_unlock(&(*philo)->self);
	if((*philo)->info->is_died == 1)
		return(2);
	pthread_mutex_lock(&(*philo)->neighbor);
	philo_print(&philo, 0,"has taken a fork");
	pthread_mutex_unlock(&(*philo)->neighbor);
	return(1);
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