/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:45:34 by yxu               #+#    #+#             */
/*   Updated: 2024/06/04 15:42:52 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// static void	*to_die(void *time_to_die)
// {
// 	usleep(time_to_die);
// 	return ("");
// }

// static void	*eat_with_left_fork(void *philo)
// {
// 	pthread_mutex_lock(((t_philo *)philo)->left_fork->mutex);
// 	usleep();
// 	return ("");
// }

// static void	*eat_with_right_fork(void *philodata)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *)philodata;
// 	timestamp();
// 	printf(" %d is sleeping\n", philo->id);
// 	pthread_mutex_lock(philo->left_fork->mutex);
// 	usleep(philo->rules->time_to_eat);
// 	return ("");
// }

// void	*philo_life(void *philodata)
// {
// 	pthread_t	die;
// 	t_philo		*philo;

// 	philo = (t_philo *)philodata;
// 	pthread_create(&die, NULL, to_die, philodata);
// 	if (philo->left_fork->is_available)
// 		eat_with_left_fork(philodata);
// 	else if (philo->right_fork->is_available)
// 		eat_with_right_fork(philodata);
// 	else
// 	to_sleep();
// 	return (NULL);
// }

int	main(int argc, char **argv)
{
	t_game			game;
	t_rules			rules;
	// pthread_t		main_thread;
	// int				i;

	rules = parse_arguments(argc, argv);
	init_game(&game, &rules);
	// i = 0;
	// while (i < *rules.num_of_philos)
	// 	pthread_create(&philos[i++], NULL, philo_life, NULL);
	// i = 0;
	// while (i < *rules.num_of_philos)
	// 	pthread_join(philos[i], NULL);
	free_game(&game);
	return (0);
}
