/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdohanic <cdohanic@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 14:21:19 by cdohanic          #+#    #+#             */
/*   Updated: 2025/08/30 18:50:35 by cdohanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philos.h"

void	cleanup_data(t_data *data)
{
	int	i;

	if (!data)
		return ;
	if (data->forks)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_mutex);
	if (data->philos)
		free(data->philos);
	if (data->threads)
		free(data->threads);
	free(data);
}

int	error_msg(char *str, t_data *data)
{
	printf("%s", str);
	if (data)
		free(data);
	exit(1);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	t_philo	*philos;

	if (argc != 5 && argc != 6)
		return (error_msg(ARGS, NULL));
	data = parse_input(argc, argv);
	if (!data)
		return (1);
	philos = init_data(data);
	if (!philos)
		return (free(data), 1);
	if (data->num_philos == 1)
	{
		one_philo(data);
		cleanup_data(data);
		return (0);
	}
	start_simulation(data);
	cleanup_data(data);
	return (0);
}
