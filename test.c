#include <stdio.h>
#include <sys/time.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "test.h"

long long int	get_ms(void)
{
	struct	timeval		tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

void    ft_usleep(long long int ms)
{
	long long int        ms_start;

	ms_start = get_ms();
	while ((get_ms() - ms_start) < ms);
}

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
		ft_usleep(s->time_to_eat);
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
		ft_usleep(s->time_to_eat);
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
	ft_usleep(s->time_to_sleep);
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
		{
			if (s->philo[i].n_eat < s->n_eat)
				i = 0;
			i++;
			if (i == s->n_philo)
			{
				s->end = true;
				break ;
			}
		}
		if (j == s->n_philo)
			j = 0;
		if ((get_ms() - s->philo[j].last_eating_time > s->time_to_die))
		{
			message(s, j, "died");
			s->end = true;
		}
		j++;
	}
	return ((void *) NULL);
}

void	*ft_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->s->end == false)
	{
		eat(philo->s, philo->id);
		philo->n_eat++;
		if (philo->s->end == true)
			break ;
		dodo(philo->s, philo->id);
		if (philo->s->end == true)
			break ;
		think(philo->s, philo->id);
	}
	return ((void *) NULL);
}

int		main(int argc, char **argv)
{
	int				i;
	pthread_t		threads[atoi(argv[1])];
	pthread_t		monitor;
	t_struct		s;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Error");
		exit(EXIT_SUCCESS);
	}
	s.end = false;
	s.time_to_die = atoi(argv[2]);
	s.time_to_eat = atoi(argv[3]);
	s.time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		s.n_eat = atoi(argv[5]);
	else
		s.n_eat = -1;
	s.n_philo = atoi(argv[1]);
	pthread_mutex_init(&s.message, NULL);
	pthread_mutex_unlock(&s.message);
	s.philo = (t_philo *)malloc(sizeof(t_philo) * s.n_philo);
	while(i < s.n_philo)
	{
		pthread_mutex_init(&s.philo[i].fork, NULL);
		pthread_mutex_unlock(&s.philo[i].fork);
		s.philo[i].s = &s;
		s.philo[i].last_eating_time = get_ms();
		s.philo[i].n_eat = 0;
		s.philo[i].id = i;
		i++;
	}
	i = 0;
	pthread_attr_t tattr;
	pthread_attr_init(&tattr);
	pthread_attr_setdetachstate(&tattr,PTHREAD_CREATE_DETACHED);
	s.start_time = get_ms();
	while (i < s.n_philo)
	{
		pthread_create(&threads[i], &tattr, &ft_philo, &s.philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, &ft_monitor, &s);
	pthread_join(monitor, (void *)&s);
	pthread_mutex_destroy(&s.message);
	i = 0;
	while (i < s.n_philo)
	{
		pthread_mutex_destroy(&s.philo[i].fork);
		i++;
	}
	free(s.philo);
}