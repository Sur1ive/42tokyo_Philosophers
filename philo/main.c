/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:45:34 by yxu               #+#    #+#             */
/*   Updated: 2024/06/05 21:38:54 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*eat_and_sleep(void *philodata)
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
	philo->status = EATING;
	usleep(philo->game->rules->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	philo->left_fork->is_available = TRUE;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	philo->right_fork->is_available = TRUE;
	philo->last_meal = now();
	timestamp(philo, "is sleeping");
	philo->status = SLEEPING;
	usleep(philo->game->rules->time_to_sleep * 1000);
	philo->status = DOING_NOTHING;
	return ("");
}

void	*life(void *philodata)
{
	t_philo		*philo;
	pthread_t	eat_thread;

	philo = (t_philo *)philodata;
	philo->last_meal = now();
	while (1)
	{
		if (philo->game->over == TRUE)
			return (NULL);
		if (philo->left_fork->is_available && philo->right_fork->is_available
			&& (philo->status == DOING_NOTHING || philo->status == THINKING))
		{
			pthread_create(&eat_thread, NULL, eat_and_sleep, philo);
			pthread_detach(eat_thread);
		}
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
}

int	main(int argc, char **argv)
{
	t_game			game;
	t_rules			rules;
	int				i;

	rules = parse_arguments(argc, argv);
	init_game(&game, &rules);
	i = 0;
	while (i < rules.num_of_philos)
	{
		pthread_create(&game.philos[i].thread, NULL, life, &game.philos[i]);
		i++;
	}
	while (1)
		;
	return (0);
}
