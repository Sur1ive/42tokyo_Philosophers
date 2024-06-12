/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:37:50 by yxu               #+#    #+#             */
/*   Updated: 2024/06/12 22:34:07 by yxu              ###   ########.fr       */
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
		rules.times_each_philo_must_eat = NOT_DEFINED;
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

static t_philo	*init_philos(int num, t_fork *forks)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)malloc(sizeof(t_philo) * num);
	if (philos == NULL)
		return (NULL);
	i = 0;
	while (i < num - 1)
	{
		philos[i].id = i + 1;
		philos[i].right_fork = &forks[i];
		philos[i + 1].left_fork = &forks[i];
		philos[i].status = DOING_NOTHING;
		philos[i].extra_thread_running = FALSE;
		i++;
	}
	philos[num - 1].id = num;
	philos[num - 1].right_fork = &forks[num - 1];
	philos[0].left_fork = &forks[num - 1];
	philos[num - 1].status = DOING_NOTHING;
	return (philos);
}

void	init_game(t_game *game, t_rules *rules)
{
	t_fork	*forks;
	t_philo	*philos;
	int		i;

	forks = init_forks(rules->num_of_philos);
	if (forks == NULL)
		error_handler(FAIL_TO_INIT, NULL);
	philos = init_philos(rules->num_of_philos, forks);
	if (philos == NULL)
	{
		free_forks(rules->num_of_philos, forks);
		error_handler(FAIL_TO_INIT, NULL);
	}
	game->status = INITIALIZING;
	game->rules = rules;
	game->forks = forks;
	game->philos = philos;
	i = 0;
	while (i < rules->num_of_philos)
		philos[i++].game = game;
}
