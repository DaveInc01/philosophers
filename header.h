/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmkhitar <dmkhitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:16:09 by dmkhitar          #+#    #+#             */
/*   Updated: 2023/01/04 19:12:48 by dmkhitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_data
{
	long long int	time_to_die;
	long long int	philos_count;
	long long int	time_to_eat;
	long long int	time_to_sleep;
	long long int	eat_max_count;
	long long int	each_finish;
	long long int	start_time;
	struct timeval	current_time;
	pthread_mutex_t	print;
}				t_data;

typedef struct s_philo
{
	int				index;
	int				iteration;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*rfork;
	int				eat_count;
	struct timeval	last_eat_time;
	t_data			*data;
}			t_philo;

long long int	ft_atoi(const char *str);
int				parser(char *elem);
long long int	sec_to(struct timeval time);
void			set_data(t_data *data, char **argv, int argc);
void			print_execution(long long int time, t_philo *philo, char *str);
void			print_die_execution(
					long long int time, t_philo *philo, char *str);
long			long int	current_timestamp(void);
void			my_usleep(long long int ms);
int				kill_philo(t_philo *philo);
void			make_philos(t_data *data, t_philo *philo,
					pthread_mutex_t *fork);
void			philo_sleep_time(t_philo *philo);
void			fork_taking(t_philo *philo);
int				live_2(t_philo *philo, struct timeval current_eat);
void			*live(void *philosopher);

#endif
