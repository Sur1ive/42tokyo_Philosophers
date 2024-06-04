/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:39:58 by yxu               #+#    #+#             */
/*   Updated: 2024/06/04 16:24:22 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <limits.h>

# define MAX_PHILOS 1000
# define NOT_DEFINED -1
# define FALSE 0
# define SUCCESS 0
# define TRUE 1
# define FAILURE 1
# define INVALID_ARGUMENTS 1
# define TOO_MANY_PHILOS 2
# define FAIL_TO_INIT 3
# define RUNTIME_ERROR 4

typedef unsigned long t_milliseconds;

typedef struct s_gamerules
{
	int				num_of_philos;
	t_milliseconds	time_to_die;
	t_milliseconds	time_to_eat;
	t_milliseconds	time_to_sleep;
	int				times_each_philo_must_eat;
}	t_rules;

typedef struct s_fork
{
	int				is_available;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int		id;
	t_fork	*left_fork;
	t_fork	*right_fork;
}	t_philo;

typedef struct s_game
{
	t_rules	*rules;
	t_philo	*philos;
	t_fork	*forks;
}	t_game;

size_t	ft_strlen(const char *str);
void	error_handler(int error_num, t_game *game);
t_rules	parse_arguments(int argc, char **argv);
int		ft_atoi(const char *str);
int		str_is_int(char *s);
void	timestamp(void);
void	free_game(t_game *game);
void	free_forks(int num, t_fork *forks);
void	init_game(t_game *game, t_rules *rules);

#endif
