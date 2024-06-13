/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:41:38 by yxu               #+#    #+#             */
/*   Updated: 2024/06/13 14:12:48 by yxu              ###   ########.fr       */
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

static int	extra_thread_running(int num, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < num)
	{
		if (philos[i++].extra_thread_running == TRUE)
			return (TRUE);
	}
	return (FALSE);
}

void	free_philos(int num, t_philo *philos)
{
	int	i;

	philos->game->status = OVER;
	while (extra_thread_running(num, philos))
		;
	i = 0;
	while (i < num)
		pthread_join(philos[i++].thread, NULL);
	free(philos);
}

void	error_handler(int error_num, t_game *game)
{
	char	*msg;

	if (game)
	{
		// 这里有bug 要用lock
		if (error_num == FAIL_TO_INIT)
			free(game->philos);
		else
			free_philos(game->rules->num_of_philos, game->philos);
		free_forks(game->rules->num_of_philos, game->forks);
	}
	if (error_num == SUCCESS)
		exit(EXIT_SUCCESS);
	else
	{
		msg = "Error\n";
		write(STDERR_FILENO, msg, ft_strlen(msg));
		printf("Error code: %d\n", error_num);
		exit(EXIT_FAILURE);
	}
}
