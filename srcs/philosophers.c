/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:24:55 by mpouce            #+#    #+#             */
/*   Updated: 2023/02/21 14:24:42 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	*philo_life(void *philosopher)
{
	long	current_time;
	t_philo	*philo;
	t_philo	*next;
	int		i;

	philo = (t_philo *) philosopher;
	i = 0;
	if (philo->philo_index % 2 == 0)
		usleep(50);
	usleep(50);
	next = philo->next;
	if (!next && philo->philo_index > 1)
		next = philo->start;
	current_time = current_timestamp();
	philo->last_eat = current_time;
	philo->current_time = current_time;
	while (i < 3 && philo->settings->gameover == 0)
	{
		philo_loop(philo, next);
		i++;
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_philo		*philosophers;
	t_settings	*settings;

	philosophers = NULL;
	if (argc < 5 || argc > 6)
	{
		printf("You died.\n");
		return (1);
	}
	generate_settings(&settings, argc, argv);
	init_philos(&philosophers, argv, &settings);
	create_threads(philosophers);
	wait_threads(philosophers);
	return (0);
}
