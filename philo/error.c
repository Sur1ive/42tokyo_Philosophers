/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:41:38 by yxu               #+#    #+#             */
/*   Updated: 2024/07/14 18:41:37 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_forks(int n_forks_inited, t_fork *forks)
{
	int	i;

	if (n_forks_inited == UNINITIALIZED)
		return ;
	i = 0;
	while (i < n_forks_inited)
		pthread_mutex_destroy(&forks[i++].mutex);
	free(forks);
}

static int	extra_thread_running(int n_philos_inited, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < n_philos_inited)
	{
		if (philos[i++].extra_thread_running == TRUE)
			return (TRUE);
	}
	return (FALSE);
}

void	free_philos(int n_philos_inited, t_philo *philos)
{
	int	i;

	if (n_philos_inited == UNINITIALIZED)
		return ;
	while (extra_thread_running(n_philos_inited, philos))
	// except current thread
		;
	i = 0;
	while (i < n_philos_inited)
		pthread_join(philos[i++].thread, NULL);
	// current thread need detach, not join
	free(philos);
}

static void	free_game(t_game *game)
{
	if (game->gameover_checker_inited != UNINITIALIZED)
		pthread_join(game->gameover_checker, NULL);
	free_philos(game->n_philos_inited, game->philos);
	free_forks(game->n_forks_inited, game->forks);
	if (game->status_lock_inited != UNINITIALIZED)
		pthread_mutex_destroy(&game->status_lock);
	if (game->time_lock_inited != UNINITIALIZED)
		pthread_mutex_destroy(&game->time_lock);
}
// ^
// pthread_mutex_destroy(&game->time_lock); // cause -fsantinize=thread error
// no destroy causes no memory leak so removed it

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
