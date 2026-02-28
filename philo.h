/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:43:53 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/28 19:09:05 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct philo t_philo;
typedef struct info t_info;

typedef struct info
{
	int	nbr_of_philo;

	int	start_time;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int is_died;
	int	nbr_must_eat ;
	t_philo	*philo;
}		t_info;

typedef struct philo
{
	pthread_mutex_t self;
	pthread_mutex_t neighbor;
	int id;
	int nb_eat;
	t_info *info;
	pthread_t p;
}		t_philo;


typedef struct global
{
	t_philo *philosoph;
	t_info info;
}		t_glob;

/* PROCESS */
void	*routine (void* var);
int	process(t_glob *var);
int	take_a_fork(t_philo *philo);

/* UTILS */
long	ft_atoi( char *str);
void	philo_print(t_philo *philo, int time, char *print);