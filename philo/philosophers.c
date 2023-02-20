/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:24:55 by mpouce            #+#    #+#             */
/*   Updated: 2023/02/20 18:11:11 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct s_settings
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat_count;
	long			start_time;
	pthread_mutex_t	print;
}	t_settings;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				philo_index;
	int				eat_count;
	pthread_mutex_t	fork;
	t_settings		*settings;
	void			*next;
}	t_philo;

long	current_timestamp(void)
{
	struct timeval	tv;
	long			result;

	gettimeofday(&tv, NULL);
	result = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	//printf("return value is %ld\n", result);
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

t_philo	*lst_new(int index, t_settings *settings)
{
	t_philo	*new_philo;
	
	new_philo = malloc(sizeof(t_philo));
	new_philo->philo_index = index;
	new_philo->thread_id = 0;
	new_philo->eat_count = 0;
	new_philo->settings = settings;
	new_philo->next = NULL;
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
	t_philo *begin;

	begin = lst_last(*lst);
	if (!begin)
		*lst = new;
	else
		begin->next = new;
}

void	init_philos(t_philo **begin, char **argv, t_settings **settings)
{
	t_philo	*new;
	int	i;
	int	max;

	i = 0;
	max = ft_mini_atoi(argv[1]);
	while (i < max)
	{
		new = lst_new(i + 1, *settings);
		lst_add_back(begin, new);
		i++;
	}
}

void	*philo_life(void *philosopher)
{
	long	current_time;
	t_philo	*philo = (t_philo *) philosopher;

	//usleep(50);
	current_time = current_timestamp();
	pthread_mutex_lock(&philo->settings->print);
	printf("%ld : Philosopher %d is doing shit.\n", current_time - philo->settings->start_time, philo->philo_index);
	pthread_mutex_unlock(&philo->settings->print);
	yousleep(50, current_time);
	current_time = current_timestamp();
	pthread_mutex_lock(&philo->settings->print);
	printf("%ld : Philosopher %d is dumb.\n", current_time - philo->settings->start_time, philo->philo_index);
	pthread_mutex_unlock(&philo->settings->print);
	return (NULL);
}

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
	//printf("start time is %ld\n", (*settings)->start_time);
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
	//printf("start time is %ld\n", settings->start_time);
	init_philos(&philosophers, argv, &settings);
	create_threads(philosophers);
	wait_threads(philosophers);
	return (0);
}