/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:42:25 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/09 17:09:57 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int ac, char **av)
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int number_of_times_each_philosopher_must_eat;
	if (ac == 5 || ac == 6)
	{
		number_of_philosophers = av[1];
		time_to_die = av[2];
		time_to_eat = av[3];
		time_to_sleep = av[4];
		if (ac == 6)
			number_of_times_each_philosopher_must_eat = av[5];
	}
	else
		return (2);
}