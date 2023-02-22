/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:39:59 by mpouce            #+#    #+#             */
/*   Updated: 2023/02/22 13:13:33 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long	current_timestamp(void)
{
	struct timeval	tv;
	long			result;

	gettimeofday(&tv, NULL);
	result = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (result);
}

void	yousleep(unsigned int time, long start, t_philo *philo)
{
	long	hungrytime;

	while (is_game_over(philo) == 0)
	{
		philo->current_time = current_timestamp();
		hungrytime = philo->current_time - philo->last_eat;
		if (hungrytime >= philo->settings->time_to_die)
		{
			kill_philosopher(philo);
		}
		if (philo->current_time - start >= time)
			return ;
	}
}

int	ft_mini_atoi(char *str)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (result > 214748364 || (result == 214748364 && str[i] - '0' > 7))
			return (-1);
		result = result * 10;
		result += (str[i] - '0');
		i++;
	}
	return (result);
}

int	ft_is_alnumplus(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlenplus(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}
