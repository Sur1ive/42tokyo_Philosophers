/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 15:45:21 by yxu               #+#    #+#             */
/*   Updated: 2024/05/19 13:20:37 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	error_handler(int error_num)
{
	char	*msg;

	(void)error_num;
	msg = "Error\n";
	write(STDERR_FILENO, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

t_rules	parse_arguments(int argc, char **argv)
{
	t_rules	rules;
	int		i;

	if (argc != 5 && argc != 6)
		error_handler(NUM_OF_ARGUMENTS_ERROR);
	i = argc;
	while (i-- > 1)
	{
		if (!str_is_int(argv[i]) || ft_atoi(argv[i]) <= 0)
			error_handler(FORMAT_OF_ARGUMENTS_ERROR);
	}
	rules.number_of_philosophers = ft_atoi(argv[1]);
	rules.time_to_die = ft_atoi(argv[2]);
	rules.time_to_eat = ft_atoi(argv[3]);
	rules.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		rules.number_of_times_each_philosopher_must_eat = NOT_DEFINED;
	return (rules);
}
