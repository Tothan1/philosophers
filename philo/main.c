/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:42:25 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/03/07 17:58:09 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*recover_map(t_info *var)
{
	t_philo	*philosoph;
	int		i;

	philosoph = malloc(sizeof(t_philo) * (var->nbr_of_philo));
	if (!philosoph)
		return (NULL);
	i = 0;
	while (i < var->nbr_of_philo)
	{
		pthread_mutex_init(&philosoph[i].self, NULL);
		pthread_mutex_init(&philosoph[i].eat, NULL);
		philosoph[i].id = i + 1;
		philosoph[i].nb_eat = 0;
		philosoph[i].fork = 0;
		philosoph[i].info = var;
		if (i == 0)
			philosoph[i].neighbor = &philosoph[var->nbr_of_philo - 1].self;
		else
			philosoph[i].neighbor = &philosoph[i - 1].self;
		i++;
	}
	return (philosoph);
}

void	initialise_struct_info(t_info *var, int ac, char **av)
{
	var->start_time = 0;
	var->nbr_of_philo = ft_atoi(av[1]);
	var->time_to_die = ft_atoi(av[2]);
	var->time_to_eat = ft_atoi(av[3]);
	var->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		var->nbr_must_eat = ft_atoi(av[5]);
	else
		var->nbr_must_eat = -1;
	var->finished = 0;
}

int	finish(t_glob *var)
{
	int	i;

	i = 0;
	if (var->info.nbr_of_philo != 1)
	{
		if (pthread_join(var->died.p, NULL) != 0)
			return (2);
		pthread_mutex_destroy(&var->info.write);
		pthread_mutex_destroy(&var->info.died);
		while (i < var->info.nbr_of_philo)
		{
			if (pthread_join(var->philosoph[i].p, NULL) != 0)
				return (2);
			i++;
		}
		i = 0;
		while (i < var->info.nbr_of_philo)
		{
			pthread_mutex_destroy(&var->philosoph[i].self);
			pthread_mutex_destroy(&var->philosoph[i].eat);
			i++;
		}
	}
	free(var->philosoph);
	return (0);
}

int	main(int ac, char **av)
{
	t_glob	global;
	int		i;

	if (ac == 5 || ac == 6)
	{
		i = 1;
		while (i < ac && 0 < ft_atoi(av[i]) && 2147483648 > ft_atoi(av[i]))
			i++;
		if (i < ac)
			return (2);
		initialise_struct_info(&global.info, ac, av);
		global.philosoph = recover_map(&global.info);
		if (global.philosoph == NULL)
			return (2);
		if (process(&global) == 2)
			return (2);
		if (finish(&global) == 2)
			return (2);
	}
	else
		return (2);
}
