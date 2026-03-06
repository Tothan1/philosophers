/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:07:32 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/03/06 16:49:37 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi( char *str)
{
	int	i;
	int	signe;
	long	nombre;

	i = 0;
	signe = 1;
	nombre = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+' )
	{
		if (str[i] == '-')
		signe *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		nombre = nombre * 10 + str[i] - '0';
		i++;
	}
	if (str[i] != '\0')
		return (0);
	nombre = signe * nombre;
	return (nombre);
}

void	philo_print(t_philo *philo, char *print)
{
	struct timeval now;
	gettimeofday(&now, NULL);
	pthread_mutex_lock(&philo->info->write);
	if (!philo->info->finished)
		printf("%ld %d %s\n", (get_time_ms(now) -  philo->info->start_time), philo->id, print);
	pthread_mutex_unlock(&philo->info->write);
}

long get_time_ms()
{
	struct timeval time;
	long time_ms;
	
	gettimeofday(&time, NULL);
	time_ms = (time.tv_sec* 1000 + time.tv_usec / 1000);
	return (time_ms);
}

int flag_died(t_philo	*philo)
{
	if ( (get_time_ms() -  philo->last_meal) >= philo->info->time_to_die)
	{
		philo_print(philo, "died");
		philo->info->finished = 1;
		return (0);
	}
	return (1);
}