/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:17:59 by mpouce            #+#    #+#             */
/*   Updated: 2023/02/21 19:06:18 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	forks_available(t_philo *philo, t_philo *next)
{
	int	flag;

	flag = 0;
	if (!next)
		return (0);
	pthread_mutex_lock(&philo->has_fork_mutex);
	pthread_mutex_lock(&next->has_fork_mutex);
	if (philo->has_fork == 1 && next->has_fork == 1)
		flag = 1;
	pthread_mutex_unlock(&philo->has_fork_mutex);
	pthread_mutex_unlock(&next->has_fork_mutex);
	return (flag);
}

int	is_game_over(t_philo *philo)
{
	pthread_mutex_lock(&philo->settings->gameover_access);
	if (philo->settings->gameover == 1)
	{
		pthread_mutex_unlock(&philo->settings->gameover_access);
		return (1);
	}
	pthread_mutex_unlock(&philo->settings->gameover_access);
	return (0);
}

void	kill_philosopher(t_philo *philo)
{
	t_philo	*next;

	if (is_game_over(philo))
		return ;
	pthread_mutex_lock(&philo->settings->print);
	printf("\033[1;31m%ld ms\t: Philosopher %d died.\033[0m\n",
		philo->current_time - philo->settings->start_time,
		philo->philo_index);
	pthread_mutex_unlock(&philo->settings->print);
	pthread_mutex_lock(&philo->settings->gameover_access);
	philo->settings->gameover = 1;
	pthread_mutex_unlock(&philo->settings->gameover_access);
	pthread_mutex_unlock(&philo->fork);
	next = philo->next;
	if (!next && philo->philo_index > 1)
		next = philo->start;
	if (next)
		pthread_mutex_unlock(&next->fork);
}

int	philo_is_full(t_philo *philo)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&philo->eat_count_mutex);
	pthread_mutex_lock(&philo->settings->max_eat_access);
	if (philo->eat_count >= philo->settings->max_eat_count)
		flag = 1;
	pthread_mutex_unlock(&philo->settings->max_eat_access);
	pthread_mutex_unlock(&philo->eat_count_mutex);
	return (flag);
}

int	max_eat_reached(t_philo *philo)
{
	t_philo	*begin;

	if (philo->philo_index > 1)
		begin = philo->start;
	else
		begin = philo;
	while (begin)
	{
		if (philo_is_full(begin) == 0)
			return (0);
		begin = begin->next;
	}
	pthread_mutex_lock(&philo->settings->gameover_access);
	philo->settings->gameover = 1;
	pthread_mutex_unlock(&philo->settings->gameover_access);
	return (1);
}
