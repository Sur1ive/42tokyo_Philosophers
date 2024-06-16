/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:32:16 by yxu               #+#    #+#             */
/*   Updated: 2024/06/16 20:54:14 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philos(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->rules->num_of_philos)
	{
		if (pthread_create(
				&game->philos[i].thread, NULL, life, &game->philos[i])
			!= SUCCESS)
		{
			game->status = FINISHING;
			free_philos(i, game->philos);
			free_forks(game->rules->num_of_philos, game->forks);
			pthread_mutex_destroy(&game->bug_lock);
			pthread_mutex_destroy(&game->time_lock);
			error_handler(FAIL_TO_INIT, NULL);
		}
		i++;
	}
}

void	*gameover_checker(void *gamedata)
{
	t_game	*game;
	int		i;

	game = (t_game *)gamedata;
	if (game->rules->times_each_philo_must_eat == -1)
		return (NULL);
	while (game->status != FINISHING)
	{
		i = 0;
		while (i < game->rules->num_of_philos)
		{
			if (game->philos[i].times_ate
				< game->rules->times_each_philo_must_eat)
				break ;
			i++;
		}
		if (i == game->rules->num_of_philos)
			error_handler(SUCCESS, game);
	}
	return (NULL);
}

void	create_gameover_checker(t_game *game)
{
	if (pthread_create(&game->gameover_checker, NULL, gameover_checker, game)
		!= SUCCESS)
	{
		game->status = FINISHING;
		free_philos(game->rules->num_of_philos, game->philos);
		free_forks(game->rules->num_of_philos, game->forks);
		pthread_mutex_destroy(&game->bug_lock);
		pthread_mutex_destroy(&game->time_lock);
		error_handler(FAIL_TO_INIT, NULL);
	}
}
