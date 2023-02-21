/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:17:59 by mpouce            #+#    #+#             */
/*   Updated: 2023/02/21 14:37:07 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	forks_available(t_philo *philo, t_philo *next)
{
	if (philo->has_fork == 1 && next->has_fork == 1)
		return (1);
	return (0);
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