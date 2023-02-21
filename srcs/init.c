/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:36:45 by mpouce            #+#    #+#             */
/*   Updated: 2023/02/21 13:38:32 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

t_philo	*lst_new(int index, t_settings *settings)
{
	t_philo	*new_philo;

	new_philo = malloc(sizeof(t_philo));
	new_philo->philo_index = index;
	new_philo->thread_id = 0;
	new_philo->eat_count = 0;
	new_philo->settings = settings;
	new_philo->next = NULL;
	new_philo->start = NULL;
	pthread_mutex_init(&new_philo->fork, NULL);
	return (new_philo);
}

t_philo	*lst_last(t_philo *lst)
{
	t_philo	*begin;

	if (!lst)
		return (0);
	begin = lst;
	while (begin->next)
	{
		begin = begin->next;
	}
	return (begin);
}

void	lst_add_back(t_philo **lst, t_philo *new)
{
	t_philo	*begin;

	begin = lst_last(*lst);
	if (!begin)
		*lst = new;
	else
	{
		begin->next = new;
		begin->start = *lst;
	}
}

void	init_philos(t_philo **begin, char **argv, t_settings **settings)
{
	t_philo	*new;
	int		i;
	int		max;

	i = 0;
	max = ft_mini_atoi(argv[1]);
	while (i < max)
	{
		new = lst_new(i + 1, *settings);
		lst_add_back(begin, new);
		i++;
	}
}

void	generate_settings(t_settings **settings, int argc, char **argv)
{
	struct timeval	tv;
	long			mseconds;

	*settings = malloc(sizeof(t_settings));
	(*settings)->time_to_die = ft_mini_atoi(argv[2]);
	(*settings)->time_to_eat = ft_mini_atoi(argv[3]);
	(*settings)->time_to_sleep = ft_mini_atoi(argv[4]);
	if (argc == 6)
		(*settings)->max_eat_count = ft_mini_atoi(argv[5]);
	else
		(*settings)->max_eat_count = -1;
	pthread_mutex_init(&(*settings)->print, NULL);
	gettimeofday(&tv, NULL);
	mseconds = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	(*settings)->start_time = mseconds;
}
