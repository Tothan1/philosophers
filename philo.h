/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:43:53 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/11 11:08:03 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct philosoph
{
	int	nb_fork;
	int id;
	pthread_t p;
}		t_philosoph;

typedef struct global
{
	int	number_of_philosophers;

	int	number_of_fork;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	t_philosoph *philosoph;
}		t_glob;