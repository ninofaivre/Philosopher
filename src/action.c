/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:12:25 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/22 15:49:00 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	take_forks_even(t_env *env, int id)
{
	if (id == 0 && env->n_philo % 2)
		pthread_mutex_lock(&env->philo_data[id + 1].fork);
	else
		pthread_mutex_lock(&env->philo_data[id].fork);
	message(env, id, "has taken a fork");
	if (id == 0 && (env->n_philo % 2))
		pthread_mutex_lock(&env->philo_data[id].fork);
	else if (id == (env->n_philo - 1))
		pthread_mutex_lock(&env->philo_data[0].fork);
	else
		pthread_mutex_lock(&env->philo_data[id + 1].fork);
	message(env, id, "has taken a fork");
}

static void	take_forks(t_env *env, int id)
{
	if (id % 2)
	{
		if (id == 1 && env->n_philo % 2)
			pthread_mutex_lock(&env->philo_data[id].fork);
		else
			pthread_mutex_lock(&env->philo_data[id - 1].fork);
		message(env, id, "has taken a fork");
		if (id == 1 && env->n_philo % 2)
			pthread_mutex_lock(&env->philo_data[env->n_philo - 1].fork);
		else
			pthread_mutex_lock(&env->philo_data[id].fork);
		message(env, id, "has taken a fork");
	}
	else
		take_forks_even(env, id);
}

static void	release_forks(t_env *env, int id)
{
	if (id % 2)
	{
		pthread_mutex_unlock(&env->philo_data[id].fork);
		if (id == 1 && env->n_philo % 2)
			pthread_mutex_unlock(&env->philo_data[env->n_philo - 1].fork);
		else
			pthread_mutex_unlock(&env->philo_data[id - 1].fork);
	}
	else
	{
		if (id == 0 && env->n_philo % 2)
			pthread_mutex_unlock(&env->philo_data[id + 1].fork);
		pthread_mutex_unlock(&env->philo_data[id].fork);
		if (id == 0 && (env->n_philo % 2))
			return ;
		else if (id == (env->n_philo - 1))
			pthread_mutex_unlock(&env->philo_data[0].fork);
		else
			pthread_mutex_unlock(&env->philo_data[id + 1].fork);
	}
}

void	eat(t_env *env, int id)
{
	take_forks(env, id);
	env->philo_data[id].last_eat = get_ms();
	message(env, id, "is eating");
	env->philo_data[id].n_eat++;
	msleep(env->time_to_eat);
	release_forks(env, id);
}

void	slumber(t_env *env, int id)
{
	message(env, id, "is sleeping");
	msleep(env->time_to_sleep);
}
