/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatsuo <mmatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:03:52 by mmatsuo           #+#    #+#             */
/*   Updated: 2023/02/15 22:00:28 by mmatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philo_routine(void *philo_void)
{
	t_philo	*philo;

	philo = philo_void;
	pthread_mutex_lock(&philo->data->philo_mtx[philo->id - 1]);
	philo->time_start = get_time();
	philo->time_last_eat = philo->time_start;
	pthread_mutex_unlock(&philo->data->philo_mtx[philo->id - 1]);
	if (philo->id % 2 == 0)
	{
		if (!philo_think(philo->data, philo))
			return (NULL);
		usleep(100);
	}
	while (1)
	{
		if (!philo_eat(philo->data, philo))
			break ;
		if (!philo_sleep(philo->data, philo))
			break ;
		if (!philo_think(philo->data, philo))
			break ;
	}
	return (NULL);
}

void	create_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_create(&data->philo[i].thread, NULL,
			philo_routine, &data->philo[i]);
		i++;
	}
	pthread_create(&data->thread_monitor, NULL, monitor, data);
	return ;
}
