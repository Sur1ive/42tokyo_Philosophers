/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:45:21 by yxu               #+#    #+#             */
/*   Updated: 2024/07/17 01:11:26 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_milliseconds	now_e(t_philo *philo)
{
	struct timeval	time_current;
	t_milliseconds	timestamp;

	if (gettimeofday(&time_current, NULL) == -1)
		error_handler(RUNTIME_ERROR, &philo->thread, philo->game);
	timestamp = time_current.tv_sec * 1000 + time_current.tv_usec / 1000;
	return (timestamp);
}

static t_milliseconds	now(void)
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
	t_game			*game;

	game = philo->game;
	pthread_mutex_lock(&game->time_lock);
	timestamp = now();
	if (timestamp == -1)
	{
		pthread_mutex_unlock(&game->time_lock);
		error_handler(RUNTIME_ERROR, &philo->thread, game);
	}
	if (get_mutex_value(&game->status, &game->status_lock) == G_START)
		printf("%lu %d %s\n", timestamp, philo->id, str);
	pthread_mutex_unlock(&game->time_lock);
}
