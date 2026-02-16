/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 19:03:54 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/16 10:25:11 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	*routine (void* var)
{
	t_philo *philo;
	struct timeval start, end;
	philo = (t_philo *)var;
	// check_is_died();
	gettimeofday(&start, NULL);
	take_a_fork(philo)
	gettimeofday(&end, NULL);
	if(((end.tv_usec - start.tv_usec) * 1000)< 200)
		philo->is_died = 1;
	return (NULL);
}
take_a_fork()
{
	
}
int	process(t_glob *var)
{
	int i = 0;
	while (i < var->number_of_philosophers)
	{
		if (pthread_create(&var->philosoph[i].p, NULL, &routine, &var->philosoph[i]) != 0)
			return (2);
		if (pthread_join(var->philosoph[i].p, NULL) != 0)
			return (2);
		i++;
	}
	return (1);
}