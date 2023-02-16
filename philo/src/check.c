/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatsuo <mmatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:02:15 by mmatsuo           #+#    #+#             */
/*   Updated: 2023/02/17 07:18:20 by mmatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	input_data(int argc, char const **argv, t_data *data)
{
	data->num_philo = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 5)
		data->philo_must_eat = LONG_MAX;
	else
		data->philo_must_eat = ft_atol(argv[5]);
}

bool	check_arg(int argc, char const **argv)
{
	if (argc < 5 || 6 < argc)
		return (print_error(ERROR_ARG_INVALID));
	if (ft_atol(argv[1]) < 1 || MAX_PHILO < ft_atol(argv[1]))
		return (print_error(ERROR_ARG_INVALID));
	check_isnum(argv);
	if (ft_atol(argv[2]) <= 0 || ft_atol(argv[2]) > INT_MAX)
		return (print_error(ERROR_ARG_INVALID));
	if (ft_atol(argv[3]) <= 0 || ft_atol(argv[3]) > INT_MAX)
		return (print_error(ERROR_ARG_INVALID));
	if (ft_atol(argv[4]) <= 0 || ft_atol(argv[4]) > INT_MAX)
		return (print_error(ERROR_ARG_INVALID));
	if (argc == 6)
	{
		if (ft_atol(argv[5]) <= 0 || ft_atol(argv[5]) > INT_MAX)
			return (print_error(ERROR_ARG_INVALID));
	}
	return (true);
}

void	check_isnum(char const **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		if (argv[i][0] == '\0')
			print_error(ERROR_ARG_INVALID);
		if (argv[i][j] == '+' || argv[i][j] == '-')
			j++;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				print_error(ERROR_ARG_INVALID);
			j++;
		}
		i++;
	}
}

int	ft_check_over(int sign, long ans, char c)
{
	long	tmp;

	tmp = LONG_MAX / 10;
	if (sign == 1)
		c++;
	if (tmp < ans || (tmp == ans && LONG_MAX % 10 + 1 < c - '0'))
		return (1);
	return (0);
}
