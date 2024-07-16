/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 21:58:55 by yxu               #+#    #+#             */
/*   Updated: 2024/07/17 01:18:03 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philo *philo)
{
	int	stat_tmp;

	pthread_mutex_lock(&philo->fork_l->mutex);
	if (philo->fork_l->status == F_USING || philo->fork_l->status == F_USED_R)
	{
		pthread_mutex_unlock(&philo->fork_l->mutex);
		return (FAILURE);
	}
	stat_tmp = philo->fork_l->status;
	philo->fork_l->status = F_USING;
	pthread_mutex_unlock(&philo->fork_l->mutex);
	pthread_mutex_lock(&philo->fork_r->mutex);
	if (philo->fork_r->status == F_USING || philo->fork_r->status == F_USED_L)
	{
		pthread_mutex_unlock(&philo->fork_r->mutex);
		set_mutex_value
		(&philo->fork_l->status, stat_tmp, &philo->fork_l->mutex);
		return (FAILURE);
	}
	philo->fork_r->status = F_USING;
	pthread_mutex_unlock(&philo->fork_r->mutex);
	timestamp(philo, "has taken a fork");
	timestamp(philo, "has taken a fork");
	return (SUCCESS);
}

static void	*eat_and_sleep_thread(void *philodata)
{
	t_philo	*philo;

	philo = (t_philo *)philodata;
	set_mutex_long(&philo->last_meal, now_e(philo), &philo->mutex);
	timestamp(philo, "is eating");
	usleep(philo->game->rules.time_to_eat * 1000);
	set_mutex_long(&philo->times_ate,
		get_mutex_long(&philo->times_ate, &philo->mutex) + 1, &philo->mutex);
	set_mutex_value
		(&philo->fork_l->status, F_USED_R, &philo->fork_l->mutex);
	set_mutex_value
		(&philo->fork_r->status, F_USED_L, &philo->fork_r->mutex);
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

void	update_philo_status(t_philo *philo)
{
	if (get_mutex_value(&philo->status, &philo->mutex) != P_BUSY
		&& take_forks(philo) == SUCCESS)
		eat_and_sleep(philo);
	else if (get_mutex_value(&philo->status, &philo->mutex) == P_FREE)
	{
		set_mutex_value(&philo->status, P_THINK, &philo->mutex);
		timestamp(philo, "is thinking");
	}
	if (now_e(philo) - get_mutex_long(&philo->last_meal, &philo->mutex)
		>= philo->game->rules.time_to_die)
	{
		timestamp(philo, "died");
		error_handler(SOMEONE_DIED, &philo->thread, philo->game);
	}
}

void	*life(void *philodata)
{
	t_philo		*philo;
	t_game		*game;

	philo = (t_philo *)philodata;
	game = philo->game;
	while (get_mutex_value(&game->status, &game->status_lock) == G_INIT)
		;
	philo->last_meal = now_e(philo);
	while (get_mutex_value(&game->status, &game->status_lock) == G_START)
	{
		update_philo_status(philo);
		usleep(1);
	}
	return (NULL);
}
