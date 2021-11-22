/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:16:56 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/22 15:49:02 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	*monitor_death(void *arg)
{
	t_env	*env;
	int		i;

	env = (t_env *)arg;
	while (env->end == false)
	{
		i = 0;
		while (i < env->n_philo)
		{
			if ((get_ms() - env->philo_data[i].last_eat > env->time_to_die))
			{
				message(env, i, "died");
				env->end = true;
			}
			i++;
		}
	}
	return ((void *) NULL);
}

static void	*monitor_n_eat(void *arg)
{
	t_env	*env;
	int		i;

	env = (t_env *)arg;
	while (env->end == false)
	{
		i = 0;
		while (env->philo_data[i].n_eat >= env->n_eat)
		{
			i++;
			if (i == env->n_philo)
				env->end = true;
		}
	}
	return ((void *) NULL);
}

void	create_and_join_monitor(t_env *env)
{
	pthread_t		thread_monitor_death;
	pthread_t		thread_monitor_n_eat;

	if (env->n_eat != -1)
		pthread_create(&thread_monitor_n_eat, NULL, &monitor_n_eat, env);
	pthread_create(&thread_monitor_death, NULL, &monitor_death, env);
	pthread_join(thread_monitor_death, (void *)env);
	if (env->n_eat != -1)
		pthread_join(thread_monitor_n_eat, (void *)env);
}
