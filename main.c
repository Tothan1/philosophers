/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:42:25 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/16 12:01:18 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>


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
	printf("%d\n", nombre);
	return (nombre);
}

t_philo	*recover_map(t_info var)
{
	t_philo	*philosoph;
	int		i;

	philosoph = malloc(sizeof(t_philo *) * (var.number_of_philosophers - 1));
	i = 0;
	while (i < (var.number_of_philosophers - 1))
	{
		philosoph[i].id = i;
		philosoph[i].nb_fork = 1;
		philosoph[i].is_died = 0;
		i++;
	}
	return (philosoph);
}


void	initialise_struct_info(t_info *var, int ac, char **av)
{
	var->number_of_philosophers = ft_atoi(av[1]);
	var->time_to_die = ft_atoi(av[2]);
	var->time_to_eat = ft_atoi(av[3]);
	var->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		var->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		var->number_of_times_each_philosopher_must_eat = -1;
}

int check_is_died(t_glob var, t_info info)
{
	int i;
	i = 0;
	while(i < info.number_of_philosophers && var.philosoph[i].is_died != 1)
		i++;
	if(i < info.number_of_philosophers && var.philosoph[i].is_died == 1)
		return(0);
	else
		return(1);
}

int	main(int ac, char **av)
{
	t_info var;
	t_glob global;
	pthread_mutex_t mutex;
	int i;
	if (ac == 5 || ac == 6)
	{
		i = 1;
		pthread_mutex_init(&mutex, NULL);
		while (i < ac &&  0 < ft_atoi(av[i]))
			i++;
		if( i < ac && 1 > ft_atoi(av[i]))
			return(2);
		return (1);
		initialise_struct_infoal(&var, ac, av);
		global.philosoph = recover_map(var);
		while ((i < var.number_of_times_each_philosopher_must_eat
			|| var.number_of_times_each_philosopher_must_eat == 1) && check_is_died(global, var))
			{
				if(process(&var) == 2)
					return(2);
				i++;
			}
			pthread_mutex_destroy(&mutex);
		}
	else
		return (2);
}
