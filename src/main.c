/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:09:21 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/22 13:16:10 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

int	parsing(t_struct *s, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (-1);
	s->n_philo = atoi_mod(argv[1]);
	s->time_to_die = atoi_mod(argv[2]);
	s->time_to_eat = atoi_mod(argv[3]);
	s->time_to_sleep = atoi_mod(argv[4]);
	if (s->n_philo == -1 || s->time_to_die == -1
		|| s->time_to_eat == -1 || s->time_to_sleep == -1)
		return (-1);
	if (argc == 6)
	{
		s->n_eat = atoi_mod(argv[5]);
		if (s->n_eat == -1)
			return (-1);
	}
	else
		s->n_eat = -1;
	return (0);
}

int	init(t_struct *s, pthread_t **threads)
{
	int	i;

	i = 0;
	*threads = (pthread_t *)malloc(sizeof(pthread_t) * s->n_philo);
	if (!threads)
		return (-1);
	s->end = false;
	pthread_mutex_init(&s->message, NULL);
	pthread_mutex_unlock(&s->message);
	s->philo = (t_philo *)malloc(sizeof(t_philo) * s->n_philo);
	if (!s->philo)
		return (-1);
	while (i < s->n_philo)
	{
		pthread_mutex_init(&s->philo[i].fork, NULL);
		pthread_mutex_unlock(&s->philo[i].fork);
		s->philo[i].s = s;
		s->philo[i].last_eating_time = get_ms();
		s->philo[i].n_eat = 0;
		s->philo[i].id = i;
		i++;
	}
	s->start_time = get_ms();
	return (0);
}

void	clean(t_struct *s, pthread_t *threads)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&s->message);
	while (i < s->n_philo)
	{
		pthread_mutex_destroy(&s->philo[i].fork);
		i++;
	}
	free(threads);
	free(s->philo);
}

int	main(int argc, char **argv)
{
	pthread_t		*threads;
	t_struct		s;

	threads = NULL;
	if (parsing(&s, argc, argv) == -1 || init(&s, &threads) == -1)
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	create_threads_philo(threads, &s);
	create_and_join_monitor(&s);
	clean(&s, threads);
}
