/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:21:24 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/30 18:06:48 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdint.h>
# include <sys/time.h>
# include <string.h>
# define FRK "has taken a fork"
# define EAT "is eating"
# define SLP "is sleeping"
# define THK "is thinking"
# define DED "died"
# define NEGNUM "Please enter only positive numbers\n"
# define ARGS "Wrong number of arguments\n"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int						id;
	_Atomic int				meals_eaten;
	_Atomic uint64_t		last_meal_time;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	t_data					*data;
}	t_philo;

typedef struct s_data
{
	int					num_philos;
	uint64_t			die_time;
	uint64_t			eat_time;
	uint64_t			sleep_time;
	uint64_t			think_time;
	int					must_eat;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_t			*threads;
	_Atomic uint64_t	start_time;
	_Atomic int			simulation_end;
}	t_data;

uint64_t	get_time(void);
int			think_time(t_data *data);
int			ft_atoi(const char *nptr, t_data *data);
t_data		*parse_input(int argc, char *argv[]);
t_philo		*init_data(t_data *data);
int			error_msg(char *str, t_data *data);
void		cleanup_data(t_data *data);
int			main(int argc, char *argv[]);
int			think_time(t_data *data);
uint64_t	get_time(void);
void		safe_sleep(t_philo *philo, uint64_t duration);
void		timestamp_message(t_philo *philo, char *msg);
void		*philosopher_routine(void *arg);
int			eat_sleep_ripit(t_philo *philo);
int			mutex_lock(t_philo *philo);
int			start_simulation(t_data *data);
void		one_philo(t_data *data);
#endif
