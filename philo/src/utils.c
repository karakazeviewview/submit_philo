/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatsuo <mmatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 20:04:26 by mmatsuo           #+#    #+#             */
/*   Updated: 2023/02/15 22:01:16 by mmatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

void	ft_putstr_fd(const char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

long	ft_atol(const char *str)
{
	int		sign;
	long	total;

	sign = 1;
	total = 0;
	while (*str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		if (sign == 1 && ft_check_over(sign, total, *str))
			return (LONG_MAX);
		if (sign == -1 && ft_check_over(sign, total, *str))
			return (LONG_MIN);
		total = total * 10 + *str - '0';
		str++;
	}
	total *= sign;
	return (total);
}
