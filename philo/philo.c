/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:58:55 by yxu               #+#    #+#             */
/*   Updated: 2024/06/18 00:08:26 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	if (philo->left_fork->is_available == FALSE)
	{
		pthread_mutex_unlock(&philo->left_fork->mutex);
		return (FAILURE);
	}
	philo->left_fork->is_available = FALSE;
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	if (philo->right_fork->is_available == FALSE)
	{
		philo->left_fork->is_available = TRUE;
		pthread_mutex_unlock(&philo->right_fork->mutex);
		return (FAILURE);
	}
	philo->right_fork->is_available = FALSE;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	timestamp(philo, "has taken a fork");
	timestamp(philo, "has taken a fork");
	return (SUCCESS);
}

static void	*eat_and_sleep_thread(void *philodata)
{
	t_philo	*philo;

	philo = (t_philo *)philodata;
	philo->last_meal = now() + philo->game->rules->time_to_eat;
	timestamp(philo, "is eating");
	usleep(philo->game->rules->time_to_eat * 1000);
	philo->times_ate++;
	philo->left_fork->is_available = TRUE;
	philo->right_fork->is_available = TRUE;
	timestamp(philo, "is sleeping");
	usleep(philo->game->rules->time_to_sleep * 1000);
	usleep(100);
	// a solution
	philo->status = DOING_NOTHING;
	philo->extra_thread_running = FALSE;
	return (NULL);
}

static void	eat_and_sleep(t_philo *philo)
{
	pthread_t	eat;

	philo->extra_thread_running = TRUE;
	philo->status = EATING_OR_SLEEPING;
	if (pthread_create(&eat, NULL, eat_and_sleep_thread, philo) != SUCCESS)
	{
		philo->extra_thread_running = FALSE;
		error_handler(RUNTIME_ERROR, philo->game);
	}
	pthread_detach(eat);
}

void	*life(void *philodata)
{
	t_philo		*philo;

	philo = (t_philo *)philodata;
	while (philo->game->status == INITIALIZING)
		;
	philo->last_meal = now();
	while (philo->game->status == START)
	{
		if (philo->status != EATING_OR_SLEEPING && take_forks(philo) == SUCCESS)
			eat_and_sleep(philo);
		else if (philo->status == DOING_NOTHING)
		{
			philo->status = THINKING;
			timestamp(philo, "is thinking");
		}
		if (now() - philo->last_meal >= philo->game->rules->time_to_die)
		{
			timestamp(philo, "died");
			error_handler(SUCCESS, philo->game);
		}
	}
	return (NULL);
}
