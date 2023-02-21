/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:42:56 by mpouce            #+#    #+#             */
/*   Updated: 2023/02/21 14:37:29 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	philo_take_fork(t_philo *philo, t_philo *target, int mode)
{
	if (mode == TAKE)
	{
		if (target)
		{
			pthread_mutex_lock(&target->fork);
			philo->current_time = current_timestamp();
			target->has_fork = 0;
			pthread_mutex_lock(&philo->settings->print);
			printf("\033[1;37m%ld ms\t: Philosopher %d has taken a fork.\n",
				philo->current_time - philo->settings->start_time,
				philo->philo_index);
			pthread_mutex_unlock(&philo->settings->print);
			return (1);
		}
	}
	else if (mode == GIVE)
	{
		if (target)
		{
			target->has_fork = 1;
			pthread_mutex_unlock(&target->fork);
		}
	}
	return (0);
}

void	philo_eat(t_philo *philo, t_philo *next)
{
	int		fork_count;

	if (is_game_over(philo))
		return ;
	fork_count = 0;
	fork_count += philo_take_fork(philo, philo, TAKE);
	fork_count += philo_take_fork(philo, next, TAKE);
	if (fork_count == 2)
	{
		philo->current_time = current_timestamp();
		philo->last_eat = philo->current_time;
		pthread_mutex_lock(&philo->settings->print);
		printf("\033[1;37m%ld ms\t: Philosopher %d is eating.\n",
			philo->current_time - philo->settings->start_time,
			philo->philo_index);
		pthread_mutex_unlock(&philo->settings->print);
	}
	yousleep(philo->settings->time_to_eat, philo->current_time);
	philo->current_time = current_timestamp();
	philo_take_fork(philo, philo, GIVE);
	philo_take_fork(philo, next, GIVE);
}

void	philo_sleep(t_philo *philo)
{
	if (is_game_over(philo))
		return ;
	philo->current_time = current_timestamp();
	pthread_mutex_lock(&philo->settings->print);
	printf("\033[1;37m%ld ms\t: Philosopher %d is sleeping.\n",
		philo->current_time - philo->settings->start_time,
		philo->philo_index);
	pthread_mutex_unlock(&philo->settings->print);
	yousleep(philo->settings->time_to_sleep, philo->current_time);
	philo->current_time = current_timestamp();
}

void	philo_think(t_philo *philo)
{
	if (is_game_over(philo))
		return ;
	philo->current_time = current_timestamp();
	pthread_mutex_lock(&philo->settings->print);
	printf("\033[1;37m%ld ms\t: Philosopher %d is thinking.\n",
		philo->current_time - philo->settings->start_time,
		philo->philo_index);
	pthread_mutex_unlock(&philo->settings->print);
}

void	philo_loop(t_philo *philo, t_philo *next)
{
	philo_eat(philo, next);
	philo_sleep(philo);
	philo_think(philo);
	philo->current_time = current_timestamp();
	if (philo->current_time - philo->last_eat > philo->settings->time_to_die)
	{
		pthread_mutex_lock(&philo->settings->print);
		printf("\033[1;31m%ld ms\t: Philosopher %d is dumb.\n",
			philo->current_time - philo->settings->start_time,
			philo->philo_index);
		pthread_mutex_unlock(&philo->settings->print);
		philo->settings->gameover = 1;
	}
}
