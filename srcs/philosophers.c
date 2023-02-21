/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:24:55 by mpouce            #+#    #+#             */
/*   Updated: 2023/02/21 19:12:17 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	philo_loop(t_philo *philo, t_philo *next)
{
	if (forks_available(philo, next))
	{
		philo_eat(philo, next);
		if (philo->settings->max_eat_count != -1 && max_eat_reached(philo))
		{
			return ;
		}
		philo_sleep(philo);
		philo_think(philo);
	}
	philo->current_time = current_timestamp();
	if (philo->current_time - philo->last_eat > philo->settings->time_to_die)
		kill_philosopher(philo);
}

void	*philo_life(void *philosopher)
{
	long	current_time;
	t_philo	*philo;
	t_philo	*next;

	philo = (t_philo *) philosopher;
	if (philo->philo_index % 2 == 0)
		usleep(50);
	usleep(50);
	next = (t_philo *) philo->next;
	if (!next && philo->philo_index > 1)
		next = (t_philo *) philo->start;
	current_time = current_timestamp();
	philo->last_eat = current_time;
	philo->current_time = current_time;
	while (is_game_over(philo) == 0)
	{
		philo_loop(philo, next);
	}
	return (NULL);
}

int	data_validation(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_is_alnumplus(argv[i]) == 0 || ft_strlenplus(argv[i]) > 10)
		{
			printf("Invalid arguments\n");
			return (1);
		}
		if (ft_mini_atoi(argv[i]) <= 0)
		{
			printf("Argument value is 0 or lower\n");
			return (1);
		}
		i++;
	}
	return (0);
}

void	free_data(t_philo *philo, t_settings *settings)
{
	t_philo	*previous;
	t_philo	*temp;

	while (philo->next)
	{
		temp = philo;
		while (temp->next)
		{
			previous = temp;
			temp = temp->next;
		}
		free(temp);
		previous->next = 0;
	}
	free(philo);
	free(settings);
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
	if (data_validation(argc, argv) == 1)
		return (1);
	generate_settings(&settings, argc, argv);
	init_philos(&philosophers, argv, &settings);
	create_threads(philosophers);
	wait_threads(philosophers);
	free_data(philosophers, settings);
	return (0);
}
