/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:41:38 by yxu               #+#    #+#             */
/*   Updated: 2024/06/04 15:41:49 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(int num, t_fork *forks)
{
	int	i;

	i = 0;
	while (i < num)
		pthread_mutex_destroy(&forks[i++].mutex);
	free(forks);
}

void	free_game(t_game *game)
{
	free(game->philos);
	free_forks(game->rules->num_of_philos, game->forks);
}

void	error_handler(int error_num, t_game *game)
{
	char	*msg;

	if (game)
		free_game(game);
	msg = "Error\n";
	write(STDERR_FILENO, msg, ft_strlen(msg));
	printf("Error code: %d\n", error_num);
	exit(EXIT_FAILURE);
}
