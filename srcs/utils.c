/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:39:59 by mpouce            #+#    #+#             */
/*   Updated: 2023/02/21 13:40:52 by mpouce           ###   ########.fr       */
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

void	yousleep(unsigned int time, long start)
{
	long	sleep_time;

	while (1)
	{
		sleep_time = current_timestamp();
		if (sleep_time - start >= time)
			return ;
	}
}

int	ft_mini_atoi(char *str)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		result = result * 10;
		result += (str[i] - '0');
		i++;
	}
	return (result);
}
