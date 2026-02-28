/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:42:25 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/28 19:43:36 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*recover_map(t_info var)
{
	t_philo	*philosoph;
	int		i;

	philosoph = malloc(sizeof(t_philo) * (var.nbr_of_philo));
	i = 0;
	while (i < (var.nbr_of_philo))
	{
		philosoph[i].id = i + 1;
		philosoph[i].nb_eat = 0;
		philosoph[i].info = &var;
		if (i == 0)
			philosoph[i].neighbor = philosoph[var.nbr_of_philo - 1].self;
		else
			philosoph[i].neighbor = philosoph[i - 1].self;
		i++;
	}
	return (philosoph);
}

void	initialise_struct_info(t_info *var, int ac, char **av)
{
	var->start_time = 0;
	var->is_died = 0;
	var->nbr_of_philo = ft_atoi(av[1]);
	var->time_to_die = ft_atoi(av[2]);
	var->time_to_eat = ft_atoi(av[3]);
	var->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		var->nbr_must_eat = ft_atoi(av[5]);
	else
		var->nbr_must_eat = -1;
}

int	check_nb_eat(t_philo *philo, t_info info)
{
	int i = 0;
	while (i < info.nbr_of_philo)
	{
		if(philo->nb_eat == info.nbr_must_eat)
			return(0);
		i++;
	}
	return (1);
}
finish()

int	main(int ac, char **av)
{
	t_glob			global;
	pthread_mutex_t	mutex;
	int				i;

	pthread_mutex_init(&mutex, NULL);
	if (ac == 5 || ac == 6)
	{
		i = 1;
		while (i < ac && 0 < ft_atoi(av[i]) && 2147483648 > ft_atoi(av[i]))
			i++;
		if (i < ac)
			return (2);
		i = 0;
		initialise_struct_info(&global.info, ac, av);
		global.philosoph = recover_map(global.info);
		if (process(&global) == 2)	
			return (2);
		while (1)
		{
			if(check_nb_eat(global.philosoph, global.info) || global.info.nbr_must_eat == -1)
				break;
			else	if(global.info.is_died != 1)
			{
				philo_print(global.philosoph, 0, "is died");
				break;
			}
		}
		finish();
		i = 0;
		while(i < global.info.nbr_of_philo)
		{
			pthread_join();
			i++;
		}
		i = 0;
		while(i < global.info.nbr_of_philo)
		{
			pthread_mutex_destroy(&global.philosoph->neighbor);
			pthread_mutex_destroy(&global.philosoph->self);
			i++;
		}
	}
	else
		return (2);
}
