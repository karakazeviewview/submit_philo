/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatsuo <mmatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:04:34 by mmatsuo           #+#    #+#             */
/*   Updated: 2023/02/15 22:00:54 by mmatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	init_philo(t_data *data, t_philo *philo, int i)
{
	philo->id = i + 1;
	philo->num_of_eaten = 0;
	philo->time_last_eat = 0;
	philo->fork_left = &data->fork_mtx[i];
	if (i == data->num_philo - 1)
		philo->fork_right = &data->fork_mtx[0];
	else
		philo->fork_right = &data->fork_mtx[i + 1];
	philo->data = data;
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < MAX_PHILO)
	{
		pthread_mutex_init(&data->philo_mtx[i], NULL);
		pthread_mutex_init(&data->fork_mtx[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->write_finish_mtx, NULL);
	return ;
}

void	init_data(int argc, char const **argv, t_data *data)
{
	int	i;

	input_data(argc, argv, data);
	init_mutex(data);
	data->is_finish = false;
	i = 0;
	while (i < data->num_philo)
	{
		init_philo(data, &data->philo[i], i);
		i++;
	}
	data->time_start = get_time();
}
