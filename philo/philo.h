/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:39:58 by yxu               #+#    #+#             */
/*   Updated: 2024/06/02 17:18:45 by yxu              ###   ########.fr       */
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

# define NOT_DEFINED -1
# define FALSE 0
# define FAILURE 0
# define TRUE 1
# define SUCCESS 1
# define MALLOC_ERROR 1
# define NUM_OF_ARGUMENTS_ERROR 2
# define FORMAT_OF_ARGUMENTS_ERROR 3
# define GET_TIME_FAILURE 4

typedef struct s_gamerules
{
	int	*num_of_philos;
	int	*time_to_die;
	int	*time_to_eat;
	int	*time_to_sleep;
	int	*times_each_philo_must_eat;
}	t_rules;

typedef struct s_fork
{
	int				*is_available;
	pthread_mutex_t	*mutex;
}	t_fork;

typedef struct s_philo
{
	int		id;
	t_fork	*left_fork;
	t_fork	*right_fork;
	t_rules	*rules;
}	t_philo;

size_t	ft_strlen(const char *str);
void	error_handler(int error_num);
t_rules	parse_arguments(int argc, char **argv);
int		ft_atoi(const char *str);
int		str_is_int(char *s);
void	timestamp(void);

#endif
