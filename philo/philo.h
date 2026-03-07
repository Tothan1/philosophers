/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-rhun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 10:43:53 by tle-rhun          #+#    #+#             */
/*   Updated: 2026/03/07 16:21:46 by tle-rhun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct philo	t_philo;
typedef struct info		t_info;

typedef struct info
{
	int					nbr_of_philo;

	long				start_time;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_must_eat;
	int					finished;
	pthread_mutex_t		write;
	pthread_mutex_t		died;
}						t_info;

typedef struct philo
{
	pthread_mutex_t		self;
	pthread_mutex_t		*neighbor;
	int					id;
	int					fork;
	int					nb_eat;
	long				last_meal;
	t_info				*info;
	pthread_t			p;
}						t_philo;

typedef struct died
{
	t_philo				*philosoph;
	t_info				info;
	pthread_t			p;
}						t_died;

typedef struct global
{
	t_philo				*philosoph;
	t_info				info;
	t_died				died;
}						t_glob;

int						finish(t_glob *var);

/* PROCESS */
void					*routine(void *var);
int						process(t_glob *var);
int						take_a_fork(t_philo *philo);

/* UTILS */
long					ft_atoi(char *str);
void					philo_print(t_philo *philo, char *print);
long					get_time_ms(void);
int						flag_died(t_philo *philo);

#endif
