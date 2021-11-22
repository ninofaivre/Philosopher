/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:09:21 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/22 15:49:00 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

static int	parsing(t_env *env, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (-1);
	env->n_philo = atoi_mod(argv[1]);
	env->time_to_die = atoi_mod(argv[2]);
	env->time_to_eat = atoi_mod(argv[3]);
	env->time_to_sleep = atoi_mod(argv[4]);
	if (env->n_philo == -1 || env->time_to_die == -1
		|| env->time_to_eat == -1 || env->time_to_sleep == -1)
		return (-1);
	if (argc == 6)
	{
		env->n_eat = atoi_mod(argv[5]);
		if (env->n_eat == -1)
			return (-1);
	}
	else
		env->n_eat = -1;
	return (0);
}

static int	init(t_env *env, pthread_t **threads_philo)
{
	int	i;

	i = 0;
	*threads_philo = (pthread_t *)malloc(sizeof(pthread_t) * env->n_philo);
	if (!threads_philo)
		return (-1);
	env->end = false;
	pthread_mutex_init(&env->message, NULL);
	pthread_mutex_unlock(&env->message);
	env->philo_data = (t_philo_data *)
		malloc(sizeof(t_philo_data) * env->n_philo);
	if (!env->philo_data)
		return (-1);
	while (i < env->n_philo)
	{
		pthread_mutex_init(&env->philo_data[i].fork, NULL);
		pthread_mutex_unlock(&env->philo_data[i].fork);
		env->philo_data[i].env = env;
		env->philo_data[i].last_eat = get_ms();
		env->philo_data[i].n_eat = 0;
		env->philo_data[i].id = i;
		i++;
	}
	env->start_time = get_ms();
	return (0);
}

static void	clean(t_env *env, pthread_t *threads_philo)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&env->message);
	while (i < env->n_philo)
	{
		pthread_mutex_destroy(&env->philo_data[i].fork);
		i++;
	}
	free(threads_philo);
	free(env->philo_data);
}

int	main(int argc, char **argv)
{
	pthread_t	*threads_philo;
	t_env		env;

	if (parsing(&env, argc, argv) == -1 || init(&env, &threads_philo) == -1)
	{
		write(2, "Error\n", 6);
		exit(EXIT_FAILURE);
	}
	create_threads_philo(threads_philo, &env);
	create_and_join_monitor(&env);
	clean(&env, threads_philo);
}
