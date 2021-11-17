#include <stdio.h>
#include <sys/time.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "test.h"

void    ft_usleep(long int ms)
{
	static struct   timeval    tv;
	long int        ms_start;

	gettimeofday(&tv, NULL);
	ms_start = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	while (true)
	{
		gettimeofday(&tv, NULL);
	   if ((((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - ms_start) == ms)
			break;
	}
}

void	message(t_struct s, int id, char *str)
{
	pthread_mutex_lock(&s->message);
	printf("%i %s\n", id, str);
	pthread_mutex_unlock(&s->message);
}

void	eat(t_struct *s, int id)
{
	if (id % 2)
	{
		pthread_mutex_lock(&s->philo[id - 1].fork, NULL);
		message(s, id, "has taken a fork");
		pthread_mutex_lock(&s->philo[id].fork, NULL);
		message(s, id, "has taken a fork");
		message(s, id, "is eating");
		ft_usleep(s.time_to_eat);
		pthread_mutex_unlock(&s->philo[id - 1].fork);
		pthread_mutex_unlock(&s->philo[id].fork);
	}
	else
	{
		pthread_mutex_lock(&s->philo[id].fork, NULL);
		message(s, id, "has taken a fork");
		if (id == (s.n_philo - 1))
			pthread_mutex_lock(&s->philo[0].fork, NULL);
		else
			pthread_mutex_lock(&s->philo[id + 1].fork, NULL);
		message(s, id, "has taken a fork");
		message(s, id, "is eating");
		ft_usleep(200);
		pthread_mutex_unlock(&s->philo[id].fork);
		if (id == (s.n_philo - 1))
			pthread_mutex_unlock(&s->philo[0].fork);
		else
			pthread_mutex_unlock(&s->philo[id + 1].fork);
	}
}

void	think(t_struct s, int id)
{
	message(s, id, "is thinking");
}

void	dodo(t_struct s, int id)
{
	message(s, id, "is thinking");
	ft_usleep(s.timem_to_sleep);
}

void	*ft_philo(void *arg)
{
	t_struct	*s;
	int			id;

	s = (t_struct *)arg;
	id = s->id;
	while (true)
	{
		eat(s, id);
		s->philo[id]->n_eat++;
		dodo(ab);
		think(ab);
	}
	return ((void *) NULL);
}

int		main(int argc, char **argv)
{
	pthread_t		threads[atoi(argv[1])];
	t_struct		s;
	static struct	timeval		tv;

	if (argc < 5 || argc > 6)
	{
		printf("Error");
		exit(EXIT_SUCCESS);
	}
	gettimeofday(&tv, NULL);
	s.start_time = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
	s.time_to_die = atoi(argv[2]);
	s.time_to_eat = atoi(argv[3]);
	s.timem_to_sleep = atoi(argv[4]);
	if (argc == 6)
		s.n_eat = atoi(argv[5])
	else
		s.n_eat = -1;
	s.n_philo = atoi(argv[1]);
	pthread_mutex_init(&s.message, NULL);
	pthread_mutex_unlock(&s.message);
	s.philo = (t_philo *)malloc(sizeof(t_philo) * s.n_philo);
	s.id = 0;
	while(s.id < s.n_philo)
	{
		p_thread_mutex_init(&s.philo[s.id].fork, NULL);
		p_thread_mutex_unlock(&s.philo[s.id].fork);
		s.philo[s.id].s = &s;
		s.philo[s.id].last_eating_time = 0;
		s.philo[s.id].n_eat = 0;
		pthread_create(&threads[s.id], NULL, &ft_philo, &s);
		s.id++;
	}
	//pthread_create(&deux, NULL, &ft_philo, &lol);
	//pthread_join(un, (void *)&lol);
	while (true)
	{
		(void)true;
	}
	pthread_mutex_destroy(&s.message);
}