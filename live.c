/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmkhitar <dmkhitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 19:46:02 by dmkhitar          #+#    #+#             */
/*   Updated: 2023/01/04 21:41:19 by dmkhitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	philo_sleep_time(t_philo *philo)
{
	print_execution ((sec_to(philo->data->current_time)
			- philo->data->start_time), philo, "is eating");
	my_usleep (philo->data->time_to_eat / 1000);
	gettimeofday(&philo->last_eat_time, NULL);
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
	print_execution ((sec_to(philo->last_eat_time)
			- philo->data->start_time), philo, "is sleeping");
	my_usleep (philo->data->time_to_sleep / 1000);
	gettimeofday(&philo->data->current_time, NULL);
	print_execution ((sec_to(philo->data->current_time)
			- philo->data->start_time), philo, "is thinking");
}

void	fork_taking(t_philo *philo)
{
	pthread_mutex_lock(philo->lfork);
	gettimeofday(&philo->data->current_time, NULL);
	print_execution ((sec_to(philo->data->current_time)
			- philo->data->start_time), philo, "has taken a lfork");
	pthread_mutex_lock(philo->rfork);
	gettimeofday(&philo->data->current_time, NULL);
	print_execution ((sec_to(philo->data->current_time)
			- philo->data->start_time), philo, "has taken a rfork");
}

int	live_2(t_philo *philo, struct timeval current_eat)
{
	while (1)
	{
		if (philo->data->eat_max_count > 0)
			if (philo->iteration >= philo->data->eat_max_count)
				return (0);
		fork_taking(philo);
		gettimeofday(&current_eat, NULL);
		if ((sec_to(current_eat) - sec_to (philo->last_eat_time))
			> philo->data->time_to_die)
		{
			print_die_execution ((sec_to(philo->data->current_time)
					- philo->data->start_time), philo, "died");
			return (0);
		}
		philo_sleep_time(philo);
		if (philo->data->eat_max_count > 0)
			if (kill_philo(philo) == 1)
				return (0);
	}
}

void	*live(void *philosopher)
{
	t_philo			*philo;
	struct timeval	current_eat;
	struct timeval	start_time;

	philo = philosopher;
	if (philo->index % 2 == 0)
		usleep (200);
	gettimeofday(&philo->last_eat_time, NULL);
	gettimeofday(&start_time, NULL);
	gettimeofday(&current_eat, NULL);
	philo->data->start_time = sec_to(start_time);
	live_2(philo, current_eat);
	return (0);
}
