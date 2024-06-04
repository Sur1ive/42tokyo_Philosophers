/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:45:21 by yxu               #+#    #+#             */
/*   Updated: 2024/06/04 21:15:33 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	timestamp(t_philo *philo, char *str)
{
	struct timeval	time_current;
	t_milliseconds	timestamp;

	if (gettimeofday(&time_current, NULL) == -1)
		error_handler(RUNTIME_ERROR, philo->game);
	timestamp = time_current.tv_sec * 1000 + time_current.tv_usec / 1000;
	printf("%lu %s\n", timestamp, str);
}
