/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:07:32 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/03/09 17:47:14 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(char *str)
{
	int		i;
	int		signe;
	long	nombre;

	i = 0;
	signe = 1;
	nombre = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
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
	pthread_mutex_lock(&philo->info->write);
	if (flag_died(philo))
		printf("%ld %d %s\n", (get_time_ms() - philo->info->start_time),
			philo->id, print);
	pthread_mutex_unlock(&philo->info->write);
}

long	get_time_ms(void)
{
	struct timeval	time;
	long			time_ms;

	gettimeofday(&time, NULL);
	time_ms = (time.tv_sec * 1000 + time.tv_usec / 1000);
	return (time_ms);
}

int	flag_died(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->died);
	if (philo->info->finished == 1)
	{
		pthread_mutex_unlock(&philo->info->died);
		return (0);
	}
	pthread_mutex_unlock(&philo->info->died);
	return (1);
}

int	monitorv2(t_glob *global, int i, int nb_philo_must_eat)
{
	while (i < global->info.nbr_of_philo)
	{
		pthread_mutex_lock(&global->philosoph[i].eat);
		if (global->philosoph[i].nb_eat == global->info.nbr_must_eat
			&& global->info.nbr_must_eat != -1)
			nb_philo_must_eat++;
		pthread_mutex_unlock(&global->philosoph[i].eat);
		pthread_mutex_lock(&global->philosoph[i].meal);
		if ((get_time_ms()
				- global->philosoph[i].last_meal) >= global->info.time_to_die
			&& global->philosoph[i].last_meal != 0)
		{
			pthread_mutex_unlock(&global->philosoph[i].meal);
			philo_print(&global->philosoph[i], "died");
			pthread_mutex_lock(&global->info.died);
			global->info.finished = 1;
			pthread_mutex_unlock(&global->info.died);
			return (-1);
		}
		pthread_mutex_unlock(&global->philosoph[i].meal);
		i++;
	}
	return (nb_philo_must_eat);
}
