/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatsuo <mmatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 00:11:55 by mmatsuo           #+#    #+#             */
/*   Updated: 2023/02/15 20:41:18 by mmatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	join_thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(data->thread_monitor, NULL);
	return ;
}

void	terminate_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&data->philo_mtx[i]);
		pthread_mutex_destroy(&data->fork_mtx[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write_finish_mtx);
}

int	main(int argc, char const *argv[])
{
	t_data	data;

	if (!check_arg(argc, argv))
		return (1);
	init_data(argc, argv, &data);
	create_thread(&data);
	join_thread(&data);
	terminate_data(&data);
	return (0);
}
