/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:58:55 by yxu               #+#    #+#             */
/*   Updated: 2024/07/14 21:58:30 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_mutex_value(int *p, pthread_mutex_t *lock)
{
	int	value;

	pthread_mutex_lock(lock);
	value = *p;
	pthread_mutex_unlock(lock);
	return (value);
}

int	get_mutex_long(long *p, pthread_mutex_t *lock)
{
	long	value;

	pthread_mutex_lock(lock);
	value = *p;
	pthread_mutex_unlock(lock);
	return (value);
}

void	set_mutex_value(int *p, int value, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	*p = value;
	pthread_mutex_unlock(lock);
}

void	set_mutex_long(long *p, long value, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	*p = value;
	pthread_mutex_unlock(lock);
}
