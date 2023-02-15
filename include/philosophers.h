/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatsuo <mmatsuo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 19:02:53 by mmatsuo           #+#    #+#             */
/*   Updated: 2023/02/15 21:29:19 by mmatsuo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define MAX_PHILO 200

# define STATE_FORK "has taken a fork"
# define STATE_EAT "is eating"
# define STATE_SLEEP "is sleeping"
# define STATE_THINK "is thinking"
# define STATE_DIED "died"

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

# define ERROR_ARG_INVALID "Error, invalid arg"

typedef struct s_philo
{
	int				id;
	int				num_of_eaten;
	time_t			time_last_eat;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	struct s_data	*data;
	pthread_t		thread;
	long			time_start;
}	t_philo;

typedef struct s_data
{
	long			num_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			philo_must_eat;
	int				dead_num;
	pthread_mutex_t	philo_mtx[MAX_PHILO];
	pthread_mutex_t	fork_mtx[MAX_PHILO];
	pthread_mutex_t	write_finish_mtx;
	bool			is_finish;
	struct s_philo	philo[MAX_PHILO];
	time_t			time_start;
	pthread_t		thread_monitor;
}	t_data;

time_t						get_time(void);
size_t						ft_strlen(const char *s);
int							ft_isdigit(int c);
void						ft_putstr_fd(const char *s, int fd);
bool						print_error(const char *str);
bool						check_arg(int argc, char const **argv);
void						input_data(int argc, char const **argv, \
	t_data *data);
void						init_mutex(t_data *data);
void						init_philo(t_data *data, t_philo *philo, \
	int i);
void						init_data(int argc, char const **argv, \
	t_data *data);
bool						print_state(t_data *data, time_t now, int id, \
	const char *state);
bool						philo_take_fork(t_data *data, t_philo *philo);
void						wait_time(t_data *data, long time_to_wait, \
	long time_start_action);
bool						philo_eat(t_data *data, t_philo *philo);
bool						philo_sleep(t_data *data, t_philo *philo);
bool						philo_think(t_data *data, t_philo *philo);
void						*philo_routine(void *philo_void);
time_t						calc_elapsed_time(time_t *start_time);
void						*monitor(void *arg_void);
void						create_thread(t_data *data);
void						join_thread(t_data *data);
void						terminate_data(t_data *data);
int							main(int argc, char const *argv[]);
int							ft_check_over(int sign, long ans, char c);
long						ft_atol(const char *str);
// static bool					is_philo_starve(t_data *arg);
// static bool					is_num_of_eat_reached(t_data *arg);
// static void					check_isnum(char const **argv);
#endif