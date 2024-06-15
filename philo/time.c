/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:45:21 by yxu               #+#    #+#             */
/*   Updated: 2024/06/13 17:17:14 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_milliseconds	now(void)
{
	struct timeval	time_current;
	t_milliseconds	timestamp;

	if (gettimeofday(&time_current, NULL) == -1)
		return (-1);
	timestamp = time_current.tv_sec * 1000 + time_current.tv_usec / 1000;
	return (timestamp);
}

void	timestamp(t_philo *philo, char *str)
{
	t_milliseconds	timestamp;

	timestamp = now();
	if (timestamp == -1)
		error_handler(RUNTIME_ERROR, philo->game);
	if (philo->game->status == START)
		printf("%lu %d %s\n", timestamp, philo->id, str);
}
