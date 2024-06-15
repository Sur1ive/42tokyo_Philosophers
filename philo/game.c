/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:32:16 by yxu               #+#    #+#             */
/*   Updated: 2024/06/15 21:47:59 by yxu              ###   ########.fr       */
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
			game->philos = NULL;
			error_handler(FAIL_TO_INIT, game);
		}
		i++;
	}
}

void	*gameover_checker(void *gamedata)
{
	t_game	*game;
	int		i;
	int		times_must_eat;
	int		all_philos_full;

	game = (t_game *)gamedata;
	times_must_eat = game->rules->times_each_philo_must_eat;
	while (game->status != FINISHING)
	{
		i = 0;
		all_philos_full = TRUE;
		while (i < game->rules->num_of_philos)
		{
			if (game->philos[i].times_ate < times_must_eat)
				all_philos_full = FALSE;
			i++;
		}
		if (all_philos_full == TRUE)
			error_handler(SUCCESS, game);
	}
	return (NULL);
}
