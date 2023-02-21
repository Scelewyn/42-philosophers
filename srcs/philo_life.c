/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:42:56 by mpouce            #+#    #+#             */
/*   Updated: 2023/02/21 13:43:26 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	philo_eat(t_philo *philo, t_philo *next)
{
	int		fork_count;

	fork_count = 0;
	pthread_mutex_lock(&philo->fork);
	fork_count++;
	philo->current_time = current_timestamp();
	pthread_mutex_lock(&philo->settings->print);
	printf("\033[1;37m%ld ms\t: Philosopher %d has taken a fork.\n", philo->current_time - philo->settings->start_time, philo->philo_index);
	pthread_mutex_unlock(&philo->settings->print);
	if (next)
	{
		pthread_mutex_lock(&next->fork);
		fork_count++;
		philo->current_time = current_timestamp();
		pthread_mutex_lock(&philo->settings->print);
		printf("\033[1;37m%ld ms\t: Philosopher %d has taken a fork.\n", philo->current_time - philo->settings->start_time, philo->philo_index);
		pthread_mutex_unlock(&philo->settings->print);
	}
	if (fork_count == 2)
	{
		philo->current_time = current_timestamp();
		philo->last_eat = philo->current_time;
		pthread_mutex_lock(&philo->settings->print);
		printf("\033[1;37m%ld ms\t: Philosopher %d is eating.\n", philo->current_time - philo->settings->start_time, philo->philo_index);
		pthread_mutex_unlock(&philo->settings->print);
	}
	yousleep(philo->settings->time_to_eat, philo->current_time);
	philo->current_time = current_timestamp();
	pthread_mutex_unlock(&philo->fork);
	if (next)
		pthread_mutex_unlock(&next->fork);
}

void	philo_sleep(t_philo *philo)
{
	philo->current_time = current_timestamp();
	pthread_mutex_lock(&philo->settings->print);
	printf("\033[1;37m%ld ms\t: Philosopher %d is sleeping.\n", philo->current_time - philo->settings->start_time, philo->philo_index);
	pthread_mutex_unlock(&philo->settings->print);
	yousleep(philo->settings->time_to_sleep, philo->current_time);
	philo->current_time = current_timestamp();
}

void	philo_think(t_philo *philo)
{
	philo->current_time = current_timestamp();
	pthread_mutex_lock(&philo->settings->print);
	printf("\033[1;37m%ld ms\t: Philosopher %d is thinking.\n", philo->current_time - philo->settings->start_time, philo->philo_index);
	pthread_mutex_unlock(&philo->settings->print);
}

void	*philo_life(void *philosopher)
{
	long	current_time;
	t_philo	*philo = (t_philo *) philosopher;
	t_philo	*next;

	if (philo->philo_index % 2 == 0)
		usleep(50);
	usleep(50);
	next = philo->next;
	if (!next && philo->philo_index > 1)
		next = philo->start;
	current_time = current_timestamp();
	philo->last_eat = current_time;
	philo->current_time = current_time;
	while (1)
	{
		philo_eat(philo, next);
		philo_sleep(philo);
		philo_think(philo);
		current_time = current_timestamp();
		if (philo->current_time - philo->last_eat > philo->settings->time_to_die)
		{
			pthread_mutex_lock(&philo->settings->print);
			printf("\033[1;31m%ld ms\t: Philosopher %d is dumb.\n", current_time - philo->settings->start_time, philo->philo_index);
			pthread_mutex_unlock(&philo->settings->print);
			break ;
		}
	}
	return (NULL);
}
