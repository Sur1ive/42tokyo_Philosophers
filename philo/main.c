/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 16:45:34 by yxu               #+#    #+#             */
/*   Updated: 2024/06/16 21:13:54 by yxu              ###   ########.fr       */
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
	create_gameover_checker(&game);
	game.status = START;
	while (1)
		;
}
