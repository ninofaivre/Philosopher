/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:12:25 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/20 17:18:54 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	message(t_struct *s, int id, char *str)
{
	pthread_mutex_lock(&s->message);
	printf("%lli %i %s\n", (get_ms() - s->start_time), id, str);
	pthread_mutex_unlock(&s->message);
}

void	eat(t_struct *s, int id)
{
	if (id % 2)
	{
		if (id == 1 && s->n_philo % 2)
		{
			pthread_mutex_lock(&s->philo[id].fork);
			message(s, id, "has taken a fork");
			pthread_mutex_lock(&s->philo[s->n_philo - 1].fork);
			message(s, id, "has taken a fork");
		}
		else
		{
			pthread_mutex_lock(&s->philo[id - 1].fork);
			message(s, id, "has taken a fork");
			pthread_mutex_lock(&s->philo[id].fork);
			message(s, id, "has taken a fork");
		}
		s->philo[id].last_eating_time = get_ms();
		message(s, id, "is eating");
		msleep(s->time_to_eat);
		pthread_mutex_unlock(&s->philo[id].fork);
		if (id == 1 && s->n_philo % 2)
			pthread_mutex_unlock(&s->philo[s->n_philo - 1].fork);
		else
			pthread_mutex_unlock(&s->philo[id - 1].fork);
	}
	else
	{
		if (id == 0 && s->n_philo % 2)
		{
			pthread_mutex_lock(&s->philo[id + 1].fork);
			message(s, id, "has taken a fork");
		}
		pthread_mutex_lock(&s->philo[id].fork);
		message(s, id, "has taken a fork");
		if (id != 0 || !(s->n_philo % 2))
		{
			if (id == (s->n_philo - 1))
				pthread_mutex_lock(&s->philo[0].fork);
			else
				pthread_mutex_lock(&s->philo[id + 1].fork);
			message(s, id, "has taken a fork");
		}
		s->philo[id].last_eating_time = get_ms();
		message(s, id, "is eating");
		msleep(s->time_to_eat);
		if (id == 0 && s->n_philo % 2)
			pthread_mutex_unlock(&s->philo[id + 1].fork);
		pthread_mutex_unlock(&s->philo[id].fork);
		if (id != 0 || !(s->n_philo % 2))
		{
			if (id == (s->n_philo - 1))
				pthread_mutex_unlock(&s->philo[0].fork);
			else
				pthread_mutex_unlock(&s->philo[id + 1].fork);
		}
	}
}

void	think(t_struct *s, int id)
{
	message(s, id, "is thinking");
}

void	dodo(t_struct *s, int id)
{
	message(s, id, "is sleeping");
	msleep(s->time_to_sleep);
}
