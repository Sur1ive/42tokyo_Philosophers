/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:32:16 by yxu               #+#    #+#             */
/*   Updated: 2024/07/15 16:05:21 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philos(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->rules.num_of_philos)
	{
		if (pthread_create
			(&game->philos[i].thread, NULL, life, &game->philos[i]) != SUCCESS)
		{
			set_mutex_value(&game->status, G_FINISH, &game->status_lock);
			error_handler(FAIL_TO_INIT, NULL, game);
		}
		game->n_philos_inited++;
		i++;
	}
}

void	*gameover_checker(void *gamedata)
{
	t_game	*game;
	int		i;

	game = (t_game *)gamedata;
	if (game->rules.times_each_philo_must_eat == -1)
		return (NULL);
	while (get_mutex_value(&game->status, &game->status_lock) != G_FINISH)
	{
		i = 0;
		while (i < game->rules.num_of_philos)
		{
			if (get_mutex_long
				(&game->philos[i].times_ate, &game->philos[i].mutex)
				< game->rules.times_each_philo_must_eat)
				break ;
			i++;
		}
		if (i == game->rules.num_of_philos)
			error_handler(SUCCESS, &game->gameover_checker, game);
	}
	return (NULL);
}

void	create_gameover_checker(t_game *game)
{
	if (pthread_create(&game->gameover_checker, NULL, gameover_checker, game)
		!= SUCCESS)
	{
		set_mutex_value(&game->status, G_FINISH, &game->status_lock);
		error_handler(FAIL_TO_INIT, NULL, game);
	}
	game->gameover_checker_inited = 1;
}
