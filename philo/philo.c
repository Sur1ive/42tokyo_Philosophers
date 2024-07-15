/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:58:55 by yxu               #+#    #+#             */
/*   Updated: 2024/07/15 20:32:53 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philo *philo)
{
	int	left_fork_stat;

	pthread_mutex_lock(&philo->left_fork->mutex);
	if (philo->left_fork->status == F_USING
		|| philo->left_fork->status == F_USED_R)
	{
		pthread_mutex_unlock(&philo->left_fork->mutex);
		return (FAILURE);
	}
	left_fork_stat = philo->left_fork->status;
	philo->left_fork->status = F_USING;
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_lock(&philo->right_fork->mutex);
	if (philo->right_fork->status == F_USING
		|| philo->right_fork->status == F_USED_L)
	{
		pthread_mutex_unlock(&philo->right_fork->mutex);
		set_mutex_value
		(&philo->left_fork->status, left_fork_stat, &philo->left_fork->mutex);
		return (FAILURE);
	}
	philo->right_fork->status = F_USING;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	timestamp(philo, "has taken a fork");
	timestamp(philo, "has taken a fork");
	return (SUCCESS);
}

static void	*eat_and_sleep_thread(void *philodata)
{
	t_philo	*philo;

	philo = (t_philo *)philodata;
	set_mutex_long(&philo->last_meal, now(), &philo->mutex);
	timestamp(philo, "is eating");
	usleep(philo->game->rules.time_to_eat * 1000);
	set_mutex_long(&philo->times_ate,
		get_mutex_long(&philo->times_ate, &philo->mutex) + 1, &philo->mutex);
	set_mutex_value
		(&philo->left_fork->status, F_USED_R, &philo->left_fork->mutex);
	set_mutex_value
		(&philo->right_fork->status, F_USED_L, &philo->right_fork->mutex);
	timestamp(philo, "is sleeping");
	usleep(philo->game->rules.time_to_sleep * 1000);
	set_mutex_value(&philo->status, P_FREE, &philo->mutex);
	return (NULL);
}

static void	eat_and_sleep(t_philo *philo)
{
	pthread_t	eat;

	set_mutex_value(&philo->status, P_BUSY, &philo->mutex);
	if (pthread_create(&eat, NULL, eat_and_sleep_thread, philo) != SUCCESS)
	{
		set_mutex_value(&philo->status, P_FREE, &philo->mutex);
		error_handler(RUNTIME_ERROR, &philo->thread, philo->game);
	}
	pthread_detach(eat);
}

static void	wait_for_start(t_game *game)
{
	while (get_mutex_value(&game->status, &game->status_lock) == G_INIT)
		;
}

void	*life(void *philodata)
{
	t_philo		*philo;
	t_game		*game;

	philo = (t_philo *)philodata;
	game = philo->game;
	wait_for_start(game);
	philo->last_meal = now();
	while (get_mutex_value(&game->status, &game->status_lock) == G_START)
	{
		if (get_mutex_value(&philo->status, &philo->mutex) != P_BUSY
			&& take_forks(philo) == SUCCESS)
			eat_and_sleep(philo);
		else if (get_mutex_value(&philo->status, &philo->mutex) == P_FREE)
		{
			set_mutex_value(&philo->status, P_THINK, &philo->mutex);
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
