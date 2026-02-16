/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:43:53 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/16 12:07:38 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct info
{
	int	number_of_philosophers;

	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}		t_info;

typedef struct philosoph
{
	int	nb_fork;
	int id;
	int is_died;
	t_info info;
	pthread_t p;
}		t_philo;


typedef struct global
{
	t_philo *philosoph; 
}		t_glob;

/* PROCESS */
void	*routine (void* var);
int	process(t_glob *var);