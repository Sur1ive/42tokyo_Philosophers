/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:45:34 by yxu               #+#    #+#             */
/*   Updated: 2024/06/05 22:26:04 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (pthread_create(&game.philos[i].thread, NULL, life, &game.philos[i])
			!= SUCCESS)
		{
			free_philos(i, game.philos);
			game.philos = NULL;
			error_handler(FAIL_TO_INIT, &game);
		}
		i++;
	}
	while (1)
		;
	return (0);
}
