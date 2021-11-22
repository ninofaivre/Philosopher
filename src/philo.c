/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:15:30 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/22 15:05:46 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	*philo(void *arg)
{
	t_philo_data	*philo;

	philo = (t_philo_data *)arg;
	while (philo->env->n_philo == 1 && philo->env->end == false)
	{
	}
	while (philo->env->end == false)
	{
		eat(philo->env, philo->id);
		if (philo->env->end == true)
			break ;
		slumber(philo->env, philo->id);
		if (philo->env->end == true)
			break ;
		message(philo->env, philo->id, "is thinking");
	}
	return ((void *) NULL);
}

void	create_threads_philo(pthread_t *threads_philo, t_env *env)
{
	int				i;
	pthread_attr_t	tattr;

	i = 0;
	pthread_attr_init(&tattr);
	pthread_attr_setdetachstate(&tattr, PTHREAD_CREATE_DETACHED);
	while (i < env->n_philo)
	{
		pthread_create(&threads_philo[i], &tattr, &philo, &env->philo_data[i]);
		i++;
	}
}
