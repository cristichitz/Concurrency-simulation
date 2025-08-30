/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:29:54 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/30 19:36:26 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	assign_fork(t_philo *philo, int i, t_data *data)
{
	if (i % 2 == 0)
	{
		philo->left_fork = &data->forks[i];
		philo->right_fork = &data->forks[(i + 1) % data->num_philos];
	}
	else
	{
		philo->left_fork = &data->forks[(i + 1) % data->num_philos];
		philo->right_fork = &data->forks[i];
	}
}

t_data	*parse_input(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	memset(data, 0, sizeof(t_data));
	data->num_philos = ft_atoi(argv[1], data);
	data->die_time = ft_atoi(argv[2], data);
	data->eat_time = ft_atoi(argv[3], data);
	data->sleep_time = ft_atoi(argv[4], data);
	data->think_time = think_time(data);
	if (argc == 6)
		data->must_eat = ft_atoi(argv[5], data);
	else
		data->must_eat = -1;
	data->simulation_end = 0;
	data->philos = NULL;
	data->forks = NULL;
	data->threads = NULL;
	return (data);
}

void	philo_default(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = get_time();
		philos[i].data = data;
		assign_fork(&philos[i], i, data);
		i++;
	}
}

t_philo	*init_data(t_data *data)
{
	t_philo	*philos;
	int		i;

	if (!data)
		return (NULL);
	philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!philos)
		return (NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return (free(philos), NULL);
	data->threads = malloc(sizeof(pthread_t) * data->num_philos);
	if (!data->threads)
		return (free(data->forks), free(philos), NULL);
	data->philos = philos;
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	philo_default(data, philos);
	return (philos);
}
