/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:21:29 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/30 17:57:29 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	timestamp_message(t_philo *philo, char *msg)
{
	uint64_t	current_time;

	pthread_mutex_lock(&philo->data->print_mutex);
	current_time = get_time() - philo->data->start_time;
	printf("%lu %d %s\n", current_time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	safe_sleep(t_philo *philo, uint64_t duration)
{
	uint64_t	start;

	start = get_time();
	while (!philo->data->simulation_end)
	{
		if (get_time() - start >= duration)
			break ;
		usleep(500);
	}
}

uint64_t	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (((uint64_t)current_time.tv_sec * 1000) + (current_time.tv_usec
			/ 1000));
}

int	think_time(t_data *data)
{
	int	think_time;

	think_time = (data->die_time - data->eat_time - data->sleep_time) / 2;
	if (think_time < 0)
		think_time = 0;
	return (think_time);
}

int	ft_atoi(const char *nptr, uint64_t *result)
{
	uint64_t	num;

	num = 0;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '+')
		nptr++;
	if (*nptr == '-')
		return (1);
	if (!(*nptr >= '0' && *nptr <= '9'))
		return (1);
	while (*nptr >= '0' && *nptr <= '9')
	{
		if (num > (INT_MAX / 10) || ((num == INT_MAX / 10) && (*nptr
					- '0') > (INT_MAX % 10)))
			return (1);
		num = num * 10 + (*nptr - '0');
		nptr++;
	}
	if (*nptr != '\0')
		return (1);
	*result = num;
	return (0);
}
