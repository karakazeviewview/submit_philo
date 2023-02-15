/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_sleep_think.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatsuo <mmatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:04:10 by mmatsuo           #+#    #+#             */
/*   Updated: 2023/02/15 20:40:29 by mmatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait_time(t_data *data, long time_to_wait, long time_start_action)
{
	usleep(time_to_wait * 800);
	while (get_time() - data->time_start < time_start_action + time_to_wait)
		usleep(100);
}

bool	philo_take_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(philo->fork_left);
	if (!print_state(data, get_time() - data->time_start, philo->id, \
		STATE_FORK) || data->num_philo == 1)
	{
		pthread_mutex_unlock(philo->fork_left);
		if (data->num_philo == 1)
			usleep(data->time_to_die * 1000 + 100);
		return (false);
	}
	pthread_mutex_lock(philo->fork_right);
	if (!print_state(data, get_time() - data->time_start, philo->id, \
		STATE_FORK))
	{
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (false);
	}
	return (true);
}

bool	philo_eat(t_data *data, t_philo *philo)
{
	if (!philo_take_fork(data, philo))
		return (false);
	pthread_mutex_lock(&data->philo_mtx[philo->id - 1]);
	philo->time_last_eat = get_time();
	if (!print_state(data, philo->time_last_eat - data->time_start, \
		philo->id, STATE_EAT))
	{
		pthread_mutex_unlock(&data->philo_mtx[philo->id - 1]);
		pthread_mutex_unlock(philo->fork_left);
		pthread_mutex_unlock(philo->fork_right);
		return (false);
	}
	philo->num_of_eaten += 1;
	pthread_mutex_unlock(&data->philo_mtx[philo->id - 1]);
	wait_time(data, data->time_to_eat, philo->time_last_eat - data->time_start);
	pthread_mutex_unlock(philo->fork_left);
	pthread_mutex_unlock(philo->fork_right);
	return (true);
}

bool	philo_sleep(t_data *data, t_philo *philo)
{
	long	time_start_sleep;

	time_start_sleep = get_time() - data->time_start;
	if (!print_state(data, time_start_sleep, philo->id, STATE_SLEEP))
		return (false);
	wait_time(data, data->time_to_sleep, time_start_sleep);
	return (true);
}

bool	philo_think(t_data *data, t_philo *philo)
{
	if (!print_state(data, get_time() - data->time_start, philo->id, \
		STATE_THINK))
		return (false);
	usleep(300);
	return (true);
}
