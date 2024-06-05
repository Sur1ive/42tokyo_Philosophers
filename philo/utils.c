/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxu <yxu@student.42tokyo.jp>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:04:13 by yxu               #+#    #+#             */
/*   Updated: 2024/05/19 13:18:49 by yxu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

static long	next_num(long num, int n, int sign)
{
	if (sign == -1 && (-num < LONG_MIN / 10
			|| (-num == LONG_MIN / 10 && n >= -(LONG_MIN % 10))))
		return (LONG_MIN);
	else if (sign == 1 && (num > LONG_MAX / 10
			|| (num == LONG_MAX / 10 && n >= LONG_MAX % 10)))
		return (LONG_MAX);
	num *= 10;
	num += n;
	return (num);
}

int	ft_atoi(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9' && num != LONG_MIN && num != LONG_MAX)
	{
		num = next_num(num, *str - '0', sign);
		str++;
	}
	return (num * sign);
}

static long	ft_atol(const char *str)
{
	long	num;
	int		sign;

	num = 0;
	sign = 1;
	if (*str == '-')
		sign *= -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		num = num * 10 + *str++ - '0';
	return (num * sign);
}

int	str_is_int(char *s)
{
	int		i;
	int		len;
	long	num;

	len = ft_strlen(s);
	if (len > 11 || (len > 1 && s[0] == '0'))
		return (FALSE);
	if (s[0] != '-' && s[0] != '+' && (s[0] < '0' || s[0] > '9'))
		return (FALSE);
	if ((s[0] == '-' || s[0] == '+') && (len == 1 || (len > 2 && s[1] == '0')))
		return (FALSE);
	i = 1;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (FALSE);
		i++;
	}
	num = ft_atol(s);
	if (num > INT_MAX || num < INT_MIN)
		return (FALSE);
	return (TRUE);
}
