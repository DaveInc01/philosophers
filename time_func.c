/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmkhitar <dmkhitar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:34:41 by dmkhitar          #+#    #+#             */
/*   Updated: 2022/12/31 14:40:00 by dmkhitar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long long int	current_timestamp(void)
{
	struct timeval	te;

	gettimeofday (&te, 0);
	return (te.tv_sec * 1000 + te.tv_usec / 1000);
}

void	my_usleep(long long int ms)
{
	double	start;

	start = current_timestamp();
	while (current_timestamp() - start < ms)
		;
}
