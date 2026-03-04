/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:43:53 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/03/04 20:55:27 by tle-rhun         ###   ########.fr       */
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
	
	long	start_time; 
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_must_eat ;
	int	finished;
	pthread_mutex_t write;
}		t_info;

typedef struct philo
{
	pthread_mutex_t self;
	pthread_mutex_t *neighbor;
	int id;
	int fork;
	int nb_eat;
	int is_died;
	long last_meal;
	t_info *info;
		pthread_t p;
}		t_philo;

typedef struct died
{
	t_philo *philosoph;
	t_info info;
	pthread_t p;
}		t_died;


typedef struct global
{
	t_philo *philosoph;
	t_info info;
	t_died died;
}		t_glob;

int	finish(t_glob *var);

/* PROCESS */
void	*routine (void* var);
int	process(t_glob *var);
int	take_a_fork(t_philo *philo);

/* UTILS */
long	ft_atoi( char *str);
void	philo_print(t_philo *philo, char *print);
long get_time_ms(struct timeval time);
void flag_died(t_philo	*philo);