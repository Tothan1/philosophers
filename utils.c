/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:07:32 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/16 18:32:06 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi( char *str)
{
	int	i;
	int	signe;
	int	nombre;

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

void	philo_print(t_philo philo, int time, char *print)
{
	philo.info.all_time += time; 
	printf("%dms %dis %s\n", time,philo.id, print);
}