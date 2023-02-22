/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:42:56 by mpouce            #+#    #+#             */
/*   Updated: 2023/02/22 12:43:47 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	philo_take_fork(t_philo *philo, t_philo *target, int mode)
{
	if (mode == TAKE)
	{
		if (target && is_game_over(philo) == 0)
		{
			pthread_mutex_lock(&target->fork);
			philo->current_time = current_timestamp();
			pthread_mutex_lock(&target->has_fork_mutex);
			target->has_fork = 0;
			pthread_mutex_unlock(&target->has_fork_mutex);
			pthread_mutex_lock(&philo->settings->print);
			printf("%ld ms\t: \033[1;33mPhilosopher %d has taken a fork.\033[0m\n",
				philo->current_time - philo->settings->start_time,
				philo->philo_index);
			pthread_mutex_unlock(&philo->settings->print);
			return (1);
		}
	}
	else if (mode == GIVE)
	{
		if (target && is_game_over(philo) == 0)
			philo_give_fork(target);
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
	if (fork_count == 2 && is_game_over(philo) == 0)
	{
		philo->current_time = current_timestamp();
		philo->last_eat = philo->current_time;
		pthread_mutex_lock(&philo->eat_count_mutex);
		philo->eat_count++;
		pthread_mutex_unlock(&philo->eat_count_mutex);
		pthread_mutex_lock(&philo->settings->print);
		printf("%ld ms\t: \033[1;32mPhilosopher %d is eating.\033[0m\n",
			philo->current_time - philo->settings->start_time,
			philo->philo_index);
		pthread_mutex_unlock(&philo->settings->print);
	}
	yousleep(philo->settings->time_to_eat, philo->current_time, philo);
	philo->current_time = current_timestamp();
	philo_take_fork(philo, philo, GIVE);
	philo_take_fork(philo, next, GIVE);
}

void	philo_sleep(t_philo *philo)
{
	if (is_game_over(philo))
		return ;
	philo->current_time = current_timestamp();
	if (is_game_over(philo))
		return ;
	pthread_mutex_lock(&philo->settings->print);
	printf("%ld ms\t: \033[1;34mPhilosopher %d is sleeping.\033[0m\n",
		philo->current_time - philo->settings->start_time,
		philo->philo_index);
	pthread_mutex_unlock(&philo->settings->print);
	yousleep(philo->settings->time_to_sleep, philo->current_time, philo);
	philo->current_time = current_timestamp();
}

void	philo_think(t_philo *philo)
{
	if (is_game_over(philo))
		return ;
	philo->current_time = current_timestamp();
	pthread_mutex_lock(&philo->settings->print);
	printf("%ld ms\t: \033[1;37mPhilosopher %d is thinking.\033[0m\n",
		philo->current_time - philo->settings->start_time,
		philo->philo_index);
	pthread_mutex_unlock(&philo->settings->print);
}

void	philo_give_fork(t_philo *target)
{
	pthread_mutex_lock(&target->has_fork_mutex);
	target->has_fork = 1;
	pthread_mutex_unlock(&target->has_fork_mutex);
	pthread_mutex_unlock(&target->fork);
}
