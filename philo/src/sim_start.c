/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:04:52 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/30 18:42:51 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philos.h"

int	death_check(t_philo *philo)
{
	uint64_t	time_since_meal;

	time_since_meal = get_time() - philo->last_meal_time;
	if (time_since_meal >= philo->data->die_time)
	{
		philo->data->simulation_end = 1;
		timestamp_message(philo, DED);
		return (1);
	}
	return (0);
}

int	all_full(t_data *data)
{
	int	i;

	if (data->must_eat == -1)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		if (data->philos[i].meals_eaten < data->must_eat)
			return (0);
		i++;
	}
	return (1);
}

void	simulation_monitor(t_data *data)
{
	int	i;

	while (!data->simulation_end)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (death_check(&data->philos[i]))
				break ;
			i++;
		}
		if (all_full(data))
			data->simulation_end = 1;
		usleep(1000);
	}
}

int	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->threads[i], NULL, philosopher_routine, &data->philos[i]) != 0)
			return (cleanup_data(data));
		i++;
	}
	data->start_time = get_time();
	simulation_monitor(data);
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_join(data->threads[i], NULL) == -1)
			return (cleanup_data(data));
		i++;
	}
	return (0);
}

void	one_philo(t_data *data)
{
	int	i;

	data->start_time = get_time();
	data->philos->last_meal_time = get_time();
	pthread_mutex_lock(data->philos->left_fork);
	timestamp_message(data->philos, FRK);
	pthread_mutex_unlock(data->philos->left_fork);
	timestamp_message(data->philos, THK);
	while (!data->simulation_end)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (death_check(&data->philos[i]))
				break ;
			i++;
		}
		if (all_full(data))
			data->simulation_end = 1;
		usleep(1000);
	}
}
