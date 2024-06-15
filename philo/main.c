/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:45:34 by yxu               #+#    #+#             */
/*   Updated: 2024/06/15 21:40:17 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_game			game;
	t_rules			rules;

	rules = parse_arguments(argc, argv);
	init_game(&game, &rules);
	create_philos(&game);
	if (pthread_create(&game.gameover_checker, NULL, gameover_checker, &game)
		!= SUCCESS)
		error_handler(RUNTIME_ERROR, &game);
	game.status = START;
	while (1)
		;
}
