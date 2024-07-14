/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:58:55 by yxu               #+#    #+#             */
/*   Updated: 2024/07/14 23:20:43 by yxu              ###   ########.fr       */
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
	set_mutex_long(&philo->last_meal,
		now() + philo->game->rules.time_to_eat, &philo->mutex);
	timestamp(philo, "is eating");
	usleep(philo->game->rules.time_to_eat * 1000);
	set_mutex_long(&philo->times_ate,
		get_mutex_long(&philo->times_ate, &philo->mutex) + 1, &philo->mutex);
	philo->left_fork->is_available = TRUE;
	philo->right_fork->is_available = TRUE;
	timestamp(philo, "is sleeping");
	usleep(philo->game->rules.time_to_sleep * 1000);
	// usleep(100);
	// a solution to prevent dying
	set_mutex_value(&philo->status, FREE, &philo->mutex);
	return (NULL);
}

static void	eat_and_sleep(t_philo *philo)
{
	pthread_t	eat;

	set_mutex_value(&philo->status, BUSY, &philo->mutex);
	if (pthread_create(&eat, NULL, eat_and_sleep_thread, philo) != SUCCESS)
	{
		set_mutex_value(&philo->status, FREE, &philo->mutex);
		error_handler(RUNTIME_ERROR, &philo->thread, philo->game);
	}
	pthread_detach(eat);
}

void	*life(void *philodata)
{
	t_philo		*philo;
	t_game		*game;

	philo = (t_philo *)philodata;
	game = philo->game;
	while (get_mutex_value(&game->status, &game->status_lock) == INITIALIZING)
		;
	philo->last_meal = now();
	while (get_mutex_value(&game->status, &game->status_lock) == START)
	{
		if (get_mutex_value(&philo->status, &philo->mutex) != BUSY
			&& take_forks(philo) == SUCCESS)
			eat_and_sleep(philo);
		else if (get_mutex_value(&philo->status, &philo->mutex) == FREE)
		{
			set_mutex_value(&philo->status, THINKING, &philo->mutex);
			timestamp(philo, "is thinking");
		}
		if (now() - get_mutex_long(&philo->last_meal, &philo->mutex)
			>= game->rules.time_to_die)
		{
			timestamp(philo, "died");
			error_handler(SOMEONE_DIED, &philo->thread, game);
		}
	}
	return (NULL);
}
