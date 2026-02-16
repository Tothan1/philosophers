/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:42:25 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/16 17:31:07 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>




t_philo	*recover_map(t_info var)
{
	t_philo	*philosoph;
	int		i;

	philosoph = malloc(sizeof(t_philo *) * (var.number_of_philosophers - 1));
	i = 0;
	while (i < (var.number_of_philosophers - 1))
	{
		philosoph[i].id = i;
		philosoph[i].is_died = 0;
		i++;
	}
	return (philosoph);
}


void	initialise_struct_info(t_info *var, int ac, char **av)
{
	var->all_time = 0;
	var->number_of_philosophers = ft_atoi(av[1]);
	var->time_to_die = ft_atoi(av[2]);
	var->time_to_eat = ft_atoi(av[3]);
	var->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		var->number_of_times_each_philosopher_must_eat = ft_atoi(av[5]);
	else
		var->number_of_times_each_philosopher_must_eat = -1;
}

int check_is_died(t_glob var)
{
	int i;
	i = 0;
	while(i < var.info.number_of_philosophers && var.philosoph[i].is_died != 1)
		i++;
	if(i < var.info.number_of_philosophers && var.philosoph[i].is_died == 1)
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
		i = 0;
		initialise_struct_infoal(&var, ac, av);
		global.philosoph = recover_map(var);
		while ((i < var.number_of_times_each_philosopher_must_eat
			|| var.number_of_times_each_philosopher_must_eat == 1) && check_is_died(global))
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
