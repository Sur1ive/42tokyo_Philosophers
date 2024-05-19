/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:39:58 by yxu               #+#    #+#             */
/*   Updated: 2024/05/19 13:19:19 by yxu              ###   ########.fr       */
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
# define TRUE 1
# define MALLOC_ERROR 1
# define NUM_OF_ARGUMENTS_ERROR 2
# define FORMAT_OF_ARGUMENTS_ERROR 3

typedef struct s_gamerules
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_rules;

size_t	ft_strlen(const char *str);
void	error_handler(int error_num);
t_rules	parse_arguments(int argc, char **argv);
int		ft_atoi(const char *str);
int		str_is_int(char *s);

#endif
