/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmkhitar <dmkhitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 17:03:12 by dmkhitar          #+#    #+#             */
/*   Updated: 2023/01/04 19:59:33 by dmkhitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	max_count_check(t_philo *philo)
{
	int	all_finish;
	int	i;

	i = 0;
	all_finish = 0;
	while (all_finish < philo->data->philos_count)
	{
		if (philo[i].iteration >= philo->data->eat_max_count)
		{
			i++;
			all_finish++;
		}
	}
	return (0);
}

void	die_check(t_philo *philo)
{
	int	i;
	int	died;

	died = 0;
	if (philo->data->eat_max_count > 0)
		if (max_count_check(philo) == 0)
			return ;
	while (died == 0)
	{
		i = -1;
		gettimeofday(&philo->data->current_time, NULL);
		while (++i < philo->data->philos_count)
		{
			if ((sec_to(philo->data->current_time)
					- sec_to(philo[i].last_eat_time))
				> philo->data->time_to_die)
			{
				pthread_mutex_lock(&philo->data->print);
				printf("%lldms %d %s\n", (sec_to(philo->data->current_time)
						- philo->data->start_time), philo[i].index, "died");
				died = 1;
				break ;
			}
		}
	}
}

int	main_2(t_data *data, pthread_mutex_t *fork_t,
		t_philo *philo, pthread_t *t_id)
{
	int	i;

	i = 0;
	if (data->philos_count < 1)
		return (0);
	philo = malloc (sizeof(t_philo) * data->philos_count);
	t_id = malloc (sizeof(pthread_t) * data->philos_count);
	make_philos(data, philo, fork_t);
	pthread_mutex_init(&data->print, NULL);
	i = -1;
	while (++i < data->philos_count)
		pthread_mutex_init(&fork_t[i], NULL);
	i = -1;
	while (++i < philo->data->philos_count)
		pthread_create(&t_id[i], NULL, live, &(philo[i]));
	i = -1;
	while (++i < philo->data->philos_count)
		gettimeofday(&philo[i].last_eat_time, NULL);
	die_check(philo);
	i = -1;
	while (++i < data->philos_count)
		pthread_mutex_destroy(&fork_t[i]);
	pthread_mutex_unlock(&data->print);
	pthread_mutex_destroy(&data->print);
	return (0);
}

int	main(int argc, char **argv)
{
	int				i;
	t_data			*data;
	t_philo			*philo;
	pthread_t		*t_id;
	pthread_mutex_t	*fork_t;

	if (argc == 5 || argc == 6)
	{
		i = 0;
		while (argv[++i])
			if (!parser(argv[i]))
				return (0);
		data = malloc (sizeof(t_data));
		set_data(data, argv, argc);
		if (data->eat_max_count == -1)
			return (0);
		fork_t = malloc (sizeof(pthread_mutex_t) * data->philos_count);
		philo = NULL;
		t_id = NULL;
		main_2(data, fork_t, philo, t_id);
	}
	return (0);
}
