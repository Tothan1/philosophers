/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:07:32 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/28 19:00:50 by tle-rhun         ###   ########.fr       */
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
	nombre = signe * nombre;
	return (nombre);
}

void	philo_print(t_philo *philo, int time, char *print)
{
	philo->info->start_time += time; 
	// void(*print);
	printf("%dms %d %s\n", philo->info->start_time, philo->id, print);
}