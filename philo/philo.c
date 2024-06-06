/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:58:55 by yxu               #+#    #+#             */
/*   Updated: 2024/06/07 01:11:19 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*eat_and_sleep_thread(void *philodata)
{
	t_philo	*philo;

	philo = (t_philo *)philodata;
	pthread_mutex_lock(&philo->left_fork->mutex);
	philo->left_fork->is_available = FALSE;
	timestamp(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork->mutex);
	philo->right_fork->is_available = FALSE;
	timestamp(philo, "has taken a fork");
	timestamp(philo, "is eating");
	philo->status = EATING_OR_SLEEPING;
	usleep(philo->game->rules->time_to_eat * 1000);
	philo->left_fork->is_available = TRUE;
	pthread_mutex_unlock(&philo->left_fork->mutex);
	philo->right_fork->is_available = TRUE;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	philo->last_meal = now();
	timestamp(philo, "is sleeping");
	usleep(philo->game->rules->time_to_sleep * 1000);
	philo->status = DOING_NOTHING;
	return (NULL);
}

static void	eat_and_sleep(t_philo *philo)
{
	pthread_t	eat;

	if (pthread_create(&eat, NULL, eat_and_sleep_thread, philo) != SUCCESS)
		error_handler(RUNTIME_ERROR, philo->game);
	pthread_detach(eat);
}

static void	think(t_philo *philo)
{
	philo->status = THINKING;
	timestamp(philo, "is thinking");
}

static void	die(t_philo *philo)
{
	timestamp(philo, "died");
	error_handler(SUCCESS, philo->game);
}

void	*life(void *philodata)
{
	t_philo		*philo;

	philo = (t_philo *)philodata;
	philo->last_meal = now();
	while (philo->game->over == FALSE)
	{
		if (philo->left_fork->is_available && philo->right_fork->is_available
			&& philo->status != EATING_OR_SLEEPING)
			eat_and_sleep(philo);
		else if (philo->status == DOING_NOTHING)
			think(philo);
		if (now() - philo->last_meal >= philo->game->rules->time_to_die)
			die(philo);
	}
	return (NULL);
}
