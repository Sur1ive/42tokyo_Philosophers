/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:39:58 by yxu               #+#    #+#             */
/*   Updated: 2024/07/17 01:17:46 by yxu              ###   ########.fr       */
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

// max num of philos supported
# define MAX_PHILOS 300

// fork status
// not available
# define F_USING 0
// available
# define F_AVA 1
//available and recently used by left philo
# define F_USED_L 2
//available and recently used by right philo
# define F_USED_R 3

// philo status
# define P_FREE 0
# define P_BUSY 1
# define P_THINK 2

// game status
# define G_UNINIT -1
# define G_INIT 0
# define G_START 1
# define G_FINISH 2

// error code
# define INVALID_ARGUMENTS 1
# define TOO_MANY_PHILOS 2
# define FAIL_TO_INIT 3
# define RUNTIME_ERROR 4
# define SOMEONE_DIED 5

# define FALSE 0
# define TRUE 1

# define SUCCESS 0
# define FAILURE 1

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
	int				status;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				status;
	long			times_ate;
	pthread_mutex_t	mutex;
	t_milliseconds	last_meal;
	pthread_t		thread;
	t_fork			*fork_l;
	t_fork			*fork_r;
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
t_milliseconds	now_e(t_philo *philo);
void			init_game(t_game *game);
void			create_philos(t_game *game);
void			create_gameover_checker(t_game *game);
void			*life(void *philodata);
void			*gameover_checker(void *gamedata);
int				get_mutex_value(int *p, pthread_mutex_t *lock);
long			get_mutex_long(long *p, pthread_mutex_t *lock);
void			set_mutex_value(int *p, int value, pthread_mutex_t *lock);
void			set_mutex_long(long *p, long value, pthread_mutex_t *lock);

#endif
