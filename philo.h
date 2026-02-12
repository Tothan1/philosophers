/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:43:53 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/12 10:02:42 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct philosoph
{
	int	nb_fork;
	int id;
	pthread_t p;
}		t_philo;

typedef struct global
{
	int	number_of_philosophers;

	int	number_of_fork;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	t_philo *philosoph;
}		t_glob;