/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:45:34 by yxu               #+#    #+#             */
/*   Updated: 2024/06/02 21:30:44 by yxu              ###   ########.fr       */
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
	t_rules			rules;
	pthread_t		main_thread;
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	int				i;

	rules = parse_arguments(argc, argv);
	philos = (pthread_t *)malloc(sizeof(pthread_t) * *rules.num_of_philos);
	forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * (*rules.num_of_philos - 1));
	i = 0;
	while (i < *rules.num_of_philos - 1)
		pthread_mutex_init(&forks[i], NULL);
	i = 0;
	while (i < *rules.num_of_philos)
		pthread_create(&philos[i++], NULL, philo_life, NULL);
	i = 0;
	while (i < *rules.num_of_philos)
		pthread_join(philos[i], NULL);
	free(philos);
	free(forks);
	i = 0;
	while (i < *rules.num_of_philos - 1)
		pthread_mutex_destroy(&forks[i]);
	return (0);
}
