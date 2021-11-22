/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:12:25 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/22 12:47:04 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	take_forks_even(t_struct *s, int id)
{
	if (id == 0 && s->n_philo % 2)
		pthread_mutex_lock(&s->philo[id + 1].fork);
	else
		pthread_mutex_lock(&s->philo[id].fork);
	message(s, id, "has taken a fork");
	if (id == 0 && (s->n_philo % 2))
		pthread_mutex_lock(&s->philo[id].fork);
	else if (id == (s->n_philo - 1))
		pthread_mutex_lock(&s->philo[0].fork);
	else
		pthread_mutex_lock(&s->philo[id + 1].fork);
	message(s, id, "has taken a fork");
}

void	take_forks(t_struct *s, int id)
{
	if (id % 2)
	{
		if (id == 1 && s->n_philo % 2)
			pthread_mutex_lock(&s->philo[id].fork);
		else
			pthread_mutex_lock(&s->philo[id - 1].fork);
		message(s, id, "has taken a fork");
		if (id == 1 && s->n_philo % 2)
			pthread_mutex_lock(&s->philo[s->n_philo - 1].fork);
		else
			pthread_mutex_lock(&s->philo[id].fork);
		message(s, id, "has taken a fork");
	}
	else
		take_forks_even(s, id);
}

void	release_forks(t_struct *s, int id)
{
	if (id % 2)
	{
		pthread_mutex_unlock(&s->philo[id].fork);
		if (id == 1 && s->n_philo % 2)
			pthread_mutex_unlock(&s->philo[s->n_philo - 1].fork);
		else
			pthread_mutex_unlock(&s->philo[id - 1].fork);
	}
	else
	{
		if (id == 0 && s->n_philo % 2)
			pthread_mutex_unlock(&s->philo[id + 1].fork);
		pthread_mutex_unlock(&s->philo[id].fork);
		if (id == 0 && (s->n_philo % 2))
			return ;
		else if (id == (s->n_philo - 1))
			pthread_mutex_unlock(&s->philo[0].fork);
		else
			pthread_mutex_unlock(&s->philo[id + 1].fork);
	}
}

void	eat(t_struct *s, int id)
{
	take_forks(s, id);
	s->philo[id].last_eating_time = get_ms();
	message(s, id, "is eating");
	msleep(s->time_to_eat);
	release_forks(s, id);
}

void	dodo(t_struct *s, int id)
{
	message(s, id, "is sleeping");
	msleep(s->time_to_sleep);
}
