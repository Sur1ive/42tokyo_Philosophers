/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:41:38 by yxu               #+#    #+#             */
/*   Updated: 2024/07/14 21:31:06 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_forks(t_game *game)
{
	int	i;

	if (game->n_forks_inited == UNINITIALIZED)
		return ;
	i = 0;
	while (i < game->n_forks_inited)
		pthread_mutex_destroy(&game->forks[i++].mutex);
	free(game->forks);
}

static int	extra_thread_running(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->n_philos_inited)
	{
		if (get_mutex_value(&game->philos[i].status,
				&game->philos[i].mutex) == EATING_OR_SLEEPING)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static void	free_philos(t_game *game)
{
	int	i;

	if (game->n_philos_inited == UNINITIALIZED)
		return ;
	while (extra_thread_running(game))
		;
	i = 0;
	while (i < game->n_philos_inited)
		pthread_join(game->philos[i++].thread, NULL);
	// current thread need detach, not join
	i = 0;
	while (i < game->n_philo_locks_inited)
		pthread_mutex_destroy(&game->philos[i++].mutex);
	free(game->philos);
}

static void	free_game(t_game *game)
{
	if (game->gameover_checker_inited != UNINITIALIZED)
		pthread_join(game->gameover_checker, NULL);
	free_philos(game);
	free_forks(game);
	if (game->status_lock_inited != UNINITIALIZED)
		pthread_mutex_destroy(&game->status_lock);
	if (game->time_lock_inited != UNINITIALIZED)
		pthread_mutex_destroy(&game->time_lock);
}

void	error_handler(int error_num, t_game *game)
{
	char	*msg;

	if (game != NULL)
	{
		pthread_mutex_lock(&game->status_lock);
		if (game->status == FINISHING)
		{
			pthread_mutex_unlock(&game->status_lock);
			return ;
		}
		game->status = FINISHING;
		pthread_mutex_unlock(&game->status_lock);
		free_game(game);
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
