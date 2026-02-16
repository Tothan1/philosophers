/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:43:53 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/02/16 17:27:04 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct info
{
	int	number_of_philosophers;

	int	all_time;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}		t_info;

typedef struct philosoph
{
	pthread_mutex_t self;
	pthread_mutex_t neighbor;
	int id;
	int is_died;
	t_info info;
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


int check_is_died(t_glob var);


/* UTILS */
int	ft_atoi( char *str);
void	philo_print(t_philo philo, int time, char *print);