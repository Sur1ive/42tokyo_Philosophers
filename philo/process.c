/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:45:21 by yxu               #+#    #+#             */
/*   Updated: 2024/06/02 14:24:34 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_handler(int error_num)
{
	char	*msg;

	msg = "Error\n";
	write(STDERR_FILENO, msg, ft_strlen(msg));
	printf("Error code: %d\n", error_num);
	exit(EXIT_FAILURE);
}

t_rules	parse_arguments(int argc, char **argv)
{
	t_rules			rules;
	int				i;

	if (argc != 5 && argc != 6)
		error_handler(NUM_OF_ARGUMENTS_ERROR);
	i = argc;
	while (i-- > 1)
	{
		if (!str_is_int(argv[i]) || ft_atoi(argv[i]) <= 0)
			error_handler(FORMAT_OF_ARGUMENTS_ERROR);
	}
	rules.num_of_philos = ft_atoi(argv[1]);
	rules.time_to_die = ft_atoi(argv[2]);
	rules.time_to_eat = ft_atoi(argv[3]);
	rules.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules.times_each_philo_must_eat = ft_atoi(argv[5]);
	else
		rules.times_each_philo_must_eat = NOT_DEFINED;
	return (rules);
}

void	timestamp(void)
{
	struct timeval	time_current;
	__suseconds_t	timestamp;

	if (gettimeofday(&time_current, NULL) == -1)
		error_handler(GET_TIME_FAILURE);
	timestamp = time_current.tv_sec * 1000 + time_current.tv_usec;
	printf("%ld", timestamp);
}
