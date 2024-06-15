/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:41:38 by yxu               #+#    #+#             */
/*   Updated: 2024/06/15 21:31:04 by yxu              ###   ########.fr       */
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

	while (extra_thread_running(num, philos))
		;
	i = 0;
	while (i < num)
		pthread_join(philos[i++].thread, NULL);
	free(philos);
}

static void	free_game(int is_thread_created, t_game *game)
{
	pthread_mutex_lock(&game->bug_lock);
	if (game->status == FINISHING)
	{
		pthread_mutex_unlock(&game->bug_lock);
		return ;
	}
	game->status = FINISHING;
	pthread_mutex_unlock(&game->bug_lock);
	if (game)
	{
		if (is_thread_created == FALSE)
			free(game->philos);
		else
		{
			pthread_join(game->gameover_checker, NULL);
			free_philos(game->rules->num_of_philos, game->philos);
		}
		free_forks(game->rules->num_of_philos, game->forks);
		pthread_mutex_destroy(&game->bug_lock);
	}
}

void	error_handler(int error_num, t_game *game)
{
	char	*msg;

	if (error_num == FAIL_TO_INIT)
		free_game(FALSE, game);
	else
		free_game(TRUE, game);
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
