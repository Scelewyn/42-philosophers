/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:41:07 by mpouce            #+#    #+#             */
/*   Updated: 2023/02/21 13:41:54 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	create_threads(t_philo *philosophers)
{
	t_philo	*begin;

	begin = philosophers;
	while (begin)
	{
		pthread_create(&begin->thread_id, NULL, philo_life, begin);
		begin = begin->next;
	}
}

void	wait_threads(t_philo *philosophers)
{
	t_philo	*begin;

	begin = philosophers;
	while (begin)
	{
		pthread_join(begin->thread_id, NULL);
		begin = begin->next;
	}
}
