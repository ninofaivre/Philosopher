/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:16:56 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/22 14:25:43 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

void	*monitor_death(void *arg)
{
	t_struct	*s;
	int			i;

	s = (t_struct *)arg;
	i = 0;
	while (s->end == false)
	{
		while ()
		if ((get_ms() - s->philo_data[i].last_eating_time > s->time_to_die))
		{
			s->end = true;
			message(s, i, "died");
			break ;
		}
		i++;
		if (i == s->n_philo)
			i = 0;
	}
	return ((void *) NULL);
}

void	*monitor_n_eat(void *arg)
{
	t_struct	*s;
	int			i;

	s = (t_struct *)arg;
	while (s->end == false)
	{
		i = 0;
		while (s->philo_data[i].n_eat >= s->n_eat && i < s->n_philo)
			i++;
		if (i == s->n_philo)
			s->end = true;
	}
	return ((void *) NULL);
}

void	create_and_join_monitor(t_struct *s)
{
	pthread_t		thread_monitor_death;
	pthread_t		thread_monitor_n_eat;

	if (s->n_eat != -1)
		pthread_create(&thread_monitor_n_eat, NULL, &monitor_n_eat, s);
	pthread_create(&thread_monitor_death, NULL, &monitor_death, s);
	pthread_join(thread_monitor_death, (void *)s);
	if (s->n_eat != -1)
		pthread_join(thread_monitor_n_eat, (void *)s);
}
