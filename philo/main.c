/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:45:34 by yxu               #+#    #+#             */
/*   Updated: 2024/06/13 17:22:33 by yxu              ###   ########.fr       */
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
			game.status = ERROR_HANDLING;
			free_philos(i, game.philos);
			game.philos = NULL;
			error_handler(FAIL_TO_INIT, &game);
		}
		i++;
	}
	game.status = START;
	while (1)
		;
}
