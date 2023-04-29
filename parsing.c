/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmkhitar <dmkhitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:15:27 by dmkhitar          #+#    #+#             */
/*   Updated: 2023/01/04 20:17:10 by dmkhitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	parser(char *elem)
{
	int	i;

	i = 0;
	while (elem[i])
	{
		if ((i == 0 && elem[i] == '+') || (elem[i] >= '0' && elem [i] <= '9'))
			i++;
		else
			return (0);
	}
	return (1);
}

long long int	sec_to(struct timeval time)
{
	long long int	result;

	return (result = (time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	set_data(t_data *data, char **argv, int argc)
{
	data->philos_count = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]) * 1000;
	data->time_to_sleep = ft_atoi(argv[4]) * 1000;
	if (argc == 6)
	{
		data->eat_max_count = ft_atoi(argv[5]);
		if (data->eat_max_count <= 0)
			data->eat_max_count = -1;
	}
	else
		data->eat_max_count = 0;
}

void	make_philos(t_data *data, t_philo *philo, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < data->philos_count)
	{
		philo[i].index = i + 1;
		philo[i].data = data;
		philo[i].iteration = 0;
		if (i == 0)
		{
			philo[i].rfork = &fork[data->philos_count - 1];
			philo[i].lfork = &fork[i];
		}
		else if (i == data->philos_count - 1)
		{
			philo[i].rfork = &fork[i - 1];
			philo[i].lfork = &fork[i];
		}
		else
		{
			philo[i].rfork = &fork[i - 1];
			philo[i].lfork = &fork[i];
		}
		i++;
	}
}
