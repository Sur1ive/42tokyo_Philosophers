/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:37:50 by yxu               #+#    #+#             */
/*   Updated: 2024/06/16 21:20:37 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_rules	parse_arguments(int argc, char **argv)
{
	t_rules			rules;
	int				i;

	if (argc != 5 && argc != 6)
		error_handler(INVALID_ARGUMENTS, NULL);
	i = argc;
	while (i-- > 1)
	{
		if (!str_is_int(argv[i]) || ft_atoi(argv[i]) <= 0)
			error_handler(INVALID_ARGUMENTS, NULL);
	}
	rules.num_of_philos = ft_atoi(argv[1]);
	if (rules.num_of_philos > MAX_PHILOS)
		error_handler(TOO_MANY_PHILOS, NULL);
	rules.time_to_die = ft_atoi(argv[2]);
	rules.time_to_eat = ft_atoi(argv[3]);
	rules.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules.times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		rules.times_each_philo_must_eat = -1;
	return (rules);
}

static t_fork	*init_forks(int num)
{
	t_fork	*forks;
	int		i;

	i = 0;
	forks = (t_fork *)malloc(sizeof(t_fork) * num);
	if (forks == NULL)
		return (NULL);
	while (i < num)
	{
		if (pthread_mutex_init(&forks[i].mutex, NULL))
		{
			free_forks(i, forks);
			return (NULL);
		}
		forks[i++].is_available = TRUE;
	}
	return (forks);
}

static t_philo	init_philo(int id, t_fork *l, t_fork *r)
{
	t_philo	philo;

	philo.id = id;
	philo.times_ate = 0;
	philo.right_fork = r;
	philo.left_fork = l;
	philo.status = DOING_NOTHING;
	philo.extra_thread_running = FALSE;
	return (philo);
}

static t_philo	*init_philos(int num, t_fork *forks)
{
	t_philo	*philos;
	int		i;

	if (forks == NULL)
		return (NULL);
	philos = (t_philo *)malloc(sizeof(t_philo) * num);
	if (philos == NULL)
		return (NULL);
	philos[0] = init_philo(0, &forks[num - 1], &forks[0]);
	i = 1;
	while (i < num)
	{
		philos[i] = init_philo(i, &forks[i - 1], &forks[i]);
		i++;
	}
	return (philos);
}

void	init_game(t_game *game, t_rules *rules)
{
	int		i;
	int		flag1;
	int		flag2;

	game->forks = init_forks(rules->num_of_philos);
	game->philos = init_philos(rules->num_of_philos, game->forks);
	flag1 = pthread_mutex_init(&game->bug_lock, NULL);
	flag2 = pthread_mutex_init(&game->time_lock, NULL);
	if (game->forks == NULL || game->philos == NULL || flag1 || flag2)
	{
		free_forks(rules->num_of_philos, game->forks);
		free(game->philos);
		if (flag1 == SUCCESS)
			pthread_mutex_destroy(&game->bug_lock);
		if (flag2 == SUCCESS)
			pthread_mutex_destroy(&game->time_lock);
		error_handler(FAIL_TO_INIT, NULL);
	}
	game->status = INITIALIZING;
	game->rules = rules;
	i = 0;
	while (i < rules->num_of_philos)
		game->philos[i++].game = game;
}
