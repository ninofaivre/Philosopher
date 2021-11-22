/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:16:56 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/22 13:00:17 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>

int	is_dead(int j, t_struct *s)
{
	if (j == s->n_philo)
			j = 0;
	if ((get_ms() - s->philo[j].last_eating_time > s->time_to_die))
	{
		message(s, j, "died");
		s->end = true;
	}
	j++;
	return (j);
}

int	does_eat_enougth(int i, t_struct *s)
{
	if (s->philo[i].n_eat < s->n_eat)
		i = 0;
	else
		i++;
	if (i == s->n_philo)
		s->end = true;
	return (i);
}

void	*ft_monitor(void *arg)
{
	t_struct	*s;
	int			i;
	int			j;

	s = (t_struct *)arg;
	i = 0;
	j = 0;
	while (s->end == false)
	{
		if (s->n_eat != -1)
			i = does_eat_enougth(i, s);
		if (s->end == true)
			break ;
		j = is_dead(j, s);
	}
	return ((void *) NULL);
}

void	create_and_join_monitor(t_struct *s)
{
	pthread_t		monitor;

	pthread_create(&monitor, NULL, &ft_monitor, s);
	pthread_join(monitor, (void *)s);
}
