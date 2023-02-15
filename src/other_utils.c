/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatsuo <mmatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:33:35 by mmatsuo           #+#    #+#             */
/*   Updated: 2023/02/15 20:42:28 by mmatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	print_state(t_data *data, time_t now, int id, const char *state)
{
	pthread_mutex_lock(&data->write_finish_mtx);
	if (data->is_finish)
	{
		pthread_mutex_unlock(&data->write_finish_mtx);
		return (false);
	}
	printf("%ld %d %s\n", now, id, state);
	pthread_mutex_unlock(&data->write_finish_mtx);
	return (true);
}

time_t	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

time_t	calc_elapsed_time(time_t *start_time)
{
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	return (timeval.tv_sec * 1000 + timeval.tv_usec / 1000 - *start_time);
}
