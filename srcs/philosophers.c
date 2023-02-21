/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpouce <mpouce@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 17:24:55 by mpouce            #+#    #+#             */
/*   Updated: 2023/02/21 13:53:13 by mpouce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

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
