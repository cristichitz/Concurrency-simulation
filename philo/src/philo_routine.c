/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 18:00:04 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/30 18:37:35 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philos.h"

int	mutex_lock(t_philo *philo)
{
	if (philo->data->simulation_end)
		return (0);
	pthread_mutex_lock(philo->left_fork);
	if (philo->data->simulation_end)
	{
		pthread_mutex_unlock(philo->left_fork);
		return (0);
	}
	timestamp_message(philo, FRK);
	pthread_mutex_lock(philo->right_fork);
	if (philo->data->simulation_end)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	timestamp_message(philo, FRK);
	return (1);
}

int	eat_sleep_ripit(t_philo *philo)
{
	timestamp_message(philo, EAT);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	safe_sleep(philo, philo->data->eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	if (philo->data->simulation_end)
		return (0);
	timestamp_message(philo, SLP);
	safe_sleep(philo, philo->data->sleep_time);
	if (philo->data->simulation_end)
		return (0);
	timestamp_message(philo, THK);
	safe_sleep(philo, philo->data->think_time);
	if (philo->data->simulation_end)
		return (0);
	return (1);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->data->start_time)
		;
	if ((philo->id - 1) % 2 == 1)
		usleep(3000);
	philo->last_meal_time = get_time();
	timestamp_message(philo, THK);
	while (!philo->data->simulation_end)
	{
		if (!mutex_lock(philo))
			break ;
		if (!eat_sleep_ripit(philo))
			break ;
	}
	return (NULL);
}
