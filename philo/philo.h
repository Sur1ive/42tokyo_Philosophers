/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:39:58 by yxu               #+#    #+#             */
/*   Updated: 2024/07/14 22:40:56 by yxu              ###   ########.fr       */
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

# define MAX_PHILOS 500

# define FREE 0
# define BUSY 1
# define THINKING 2

# define FALSE 0
# define TRUE 1

# define SUCCESS 0
# define FAILURE 1

# define UNINITIALIZED -1
# define INITIALIZING 0
# define START 1
# define FINISHING 2

# define INVALID_ARGUMENTS 1
# define TOO_MANY_PHILOS 2
# define FAIL_TO_INIT 3
# define RUNTIME_ERROR 4
# define SOMEONE_DIED 5

struct			s_game;
typedef long	t_milliseconds;

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
	int				id;
	int				status;
	long			times_ate;
	pthread_mutex_t	mutex;
	int				mutex_inited;
	t_milliseconds	last_meal;
	pthread_t		thread;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct s_game	*game;
}	t_philo;

typedef struct s_game
{
	int				status;
	t_rules			rules;
	t_philo			*philos;
	t_fork			*forks;
	pthread_mutex_t	status_lock;
	pthread_mutex_t	time_lock;
	pthread_t		gameover_checker;
	int				n_philos_inited;
	int				n_philo_locks_inited;
	int				n_forks_inited;
	int				status_lock_inited;
	int				time_lock_inited;
	int				gameover_checker_inited;
}	t_game;

size_t			ft_strlen(const char *str);
int				ft_atoi(const char *str);
int				str_is_int(char *s);
void			error_handler(int error_num, pthread_t *thread, t_game *game);
t_rules			parse_arguments(int argc, char **argv);
void			timestamp(t_philo *philo, char *str);
t_milliseconds	now(void);
void			init_game(t_game *game);
void			create_philos(t_game *game);
void			create_gameover_checker(t_game *game);
void			*life(void *philodata);
void			*gameover_checker(void *gamedata);
int				get_mutex_value(int *p, pthread_mutex_t *lock);
int				get_mutex_long(long *p, pthread_mutex_t *lock);
void			set_mutex_value(int *p, int value, pthread_mutex_t *lock);
void			set_mutex_long(long *p, long value, pthread_mutex_t *lock);

#endif
