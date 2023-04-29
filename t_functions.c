/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_functions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmkhitar <dmkhitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:22:01 by dmkhitar          #+#    #+#             */
/*   Updated: 2023/01/04 19:53:58 by dmkhitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_execution(long long int time, t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lldms %d %s\n", time, philo->index, str);
	pthread_mutex_unlock(&philo->data->print);
}

void	print_die_execution(long long int time, t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print);
	printf("%lldms %d %s\n", time, philo->index, str);
}

int	kill_philo(t_philo *philo)
{
	philo->iteration += 1;
	if (philo->iteration >= philo->data->eat_max_count)
		return (1);
	return (0);
}
