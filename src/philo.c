/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:15:30 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/22 14:49:05 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*philo(void *arg)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)arg;
	while (philo->s->n_philo == 1 && philo->s->end == false)
	{
	}
	while (philo->s->end == false)
	{
		eat(philo->s, philo->id);
		if (philo->s->end == true)
			break ;
		dodo(philo->s, philo->id);
		if (philo->s->end == true)
			break ;
		message(philo->s, philo->id, "is thinking");
	}
	return ((void *) NULL);
}

void	create_threads_philo(pthread_t *threads_philo, t_struct *s)
{
	int				i;
	pthread_attr_t	tattr;

	i = 0;
	pthread_attr_init(&tattr);
	pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);
	while (i < s->n_philo)
	{
		pthread_create(&threads_philo[i], &tattr, &philo, &s->philo_data[i]);
		i++;
	}
}
