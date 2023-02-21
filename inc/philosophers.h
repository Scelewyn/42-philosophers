/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:34:14 by mpouce            #+#    #+#             */
/*   Updated: 2023/02/21 14:37:16 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_settings
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat_count;
	long			start_time;
	pthread_mutex_t	gameover_access;
	int				gameover;
	pthread_mutex_t	print;
}	t_settings;

typedef struct s_philo
{
	pthread_t		thread_id;
	int				philo_index;
	int				eat_count;
	long			last_eat;
	long			current_time;
	int				has_fork;
	pthread_mutex_t	fork;
	t_settings		*settings;
	void			*next;
	void			*start;
}	t_philo;

# define TAKE 0
# define GIVE 1

/* main.c */
void	*philo_life(void *philosopher);
int		main(int argc, char *argv[]);

/* philo_life.c */
int		philo_take_fork(t_philo *philo, t_philo *target, int mode);
void	philo_eat(t_philo *philo, t_philo *next);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	philo_loop(t_philo *philo, t_philo *next);

/* philo_life_utils.c */
int		forks_available(t_philo *philo, t_philo *next);
int		is_game_over(t_philo *philo);

/* init.c */
t_philo	*lst_new(int index, t_settings *settings);
t_philo	*lst_last(t_philo *lst);
void	lst_add_back(t_philo **lst, t_philo *new);
void	init_philos(t_philo **begin, char **argv, t_settings **settings);
void	generate_settings(t_settings **settings, int argc, char **argv);

/* utils.c */
long	current_timestamp(void);
void	yousleep(unsigned int time, long start);
int		ft_mini_atoi(char *str);

/* threads.c */
void	create_threads(t_philo *philosophers);
void	wait_threads(t_philo *philosophers);

#endif