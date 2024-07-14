/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:37:50 by yxu               #+#    #+#             */
/*   Updated: 2024/07/14 22:36:01 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_rules	parse_arguments(int argc, char **argv)
{
	t_rules			rules;
	int				i;

	if (argc != 5 && argc != 6)
		error_handler(INVALID_ARGUMENTS, NULL, NULL);
	i = argc;
	while (i-- > 1)
	{
		if (!str_is_int(argv[i]) || ft_atoi(argv[i]) <= 0)
			error_handler(INVALID_ARGUMENTS, NULL, NULL);
	}
	rules.num_of_philos = ft_atoi(argv[1]);
	if (rules.num_of_philos > MAX_PHILOS)
		error_handler(TOO_MANY_PHILOS, NULL, NULL);
	rules.time_to_die = ft_atoi(argv[2]);
	rules.time_to_eat = ft_atoi(argv[3]);
	rules.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules.times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		rules.times_each_philo_must_eat = -1;
	return (rules);
}

static void	init_forks(t_game *game)
{
	int		i;

	game->forks = (t_fork *)malloc(sizeof(t_fork) * game->rules.num_of_philos);
	if (game->forks == NULL)
		error_handler(FAIL_TO_INIT, NULL, game);
	i = 0;
	game->n_forks_inited = 0;
	while (i < game->rules.num_of_philos)
	{
		if (pthread_mutex_init(&game->forks[i].mutex, NULL))
			error_handler(FAIL_TO_INIT, NULL, game);
		game->n_forks_inited++;
		game->forks[i++].is_available = TRUE;
	}
}

static t_philo	init_philo(t_game *game, int id, t_fork *l, t_fork *r)
{
	t_philo	philo;

	philo.game = game;
	philo.id = id;
	philo.times_ate = 0;
	philo.right_fork = r;
	philo.left_fork = l;
	philo.status = FREE;
	if (pthread_mutex_init(&game->philos[id - 1].mutex, NULL))
		error_handler(FAIL_TO_INIT, NULL, game);
	game->n_philo_locks_inited++;
	return (philo);
}

static void	init_philos(t_game *game)
{
	int		i;

	game->philos = (t_philo *)
		malloc(sizeof(t_philo) * game->rules.num_of_philos);
	if (game->philos == NULL)
		error_handler(FAIL_TO_INIT, NULL, game);
	game->n_philos_inited = 0;
	game->n_philo_locks_inited = 0;
	game->philos[0] = init_philo
		(game, 1, &game->forks[game->rules.num_of_philos - 1], &game->forks[0]);
	i = 1;
	while (i < game->rules.num_of_philos)
	{
		game->philos[i] = init_philo
			(game, i + 1, &game->forks[i - 1], &game->forks[i]);
		i++;
	}
}

void	init_game(t_game *game)
{
	game->n_forks_inited = UNINITIALIZED;
	game->n_philos_inited = UNINITIALIZED;
	game->status_lock_inited = UNINITIALIZED;
	game->time_lock_inited = UNINITIALIZED;
	game->gameover_checker_inited = UNINITIALIZED;
	game->n_forks_inited = UNINITIALIZED;
	game->status = INITIALIZING;
	init_forks(game);
	init_philos(game);
	if (pthread_mutex_init(&game->status_lock, NULL))
		error_handler(FAIL_TO_INIT, NULL, game);
	game->status_lock_inited = 1;
	if (pthread_mutex_init(&game->time_lock, NULL))
		error_handler(FAIL_TO_INIT, NULL, game);
	game->time_lock_inited = 1;
}
