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

void	put_str(char *str, int i)
{
	char c;

	c = (char)(i + 48);
	while (*str)
		write(1, &(*str++), 1);
	write(1, &c, 1);
	write(1, "\n", 1);
}

void	message(t_test *ab, char *str)
{
	pthread_mutex_lock(&ab->voice);
	put_str(str, ab->i);
	pthread_mutex_unlock(&ab->voice);
}

void	eat(t_test *ab)
{
	pthread_mutex_lock(&ab->spoon);
	message(ab, "I'm eating ");
	ft_usleep(200);
	pthread_mutex_unlock(&ab->spoon);
}

void	think(t_test *ab)
{
	message(ab, "I'm thinking ");
	ft_usleep(200);
}

void	dodo(t_test *ab)
{
	message(ab, "I'm sleeping ");
	ft_usleep(200);
}

void	*ft_philo(void *lol)
{
	t_test *ab;

	ab = (t_test *)lol;
	int j = 4;
	while (j--)
	{
		eat(ab);
		think(ab);
		dodo(ab);
	}
	return ((void *) NULL);
}

int		main()
{
	pthread_t		un, deux;
	t_test			lol;
	lol.i = 0;

	pthread_mutex_init(&lol.spoon, NULL);
	pthread_mutex_init(&lol.voice, NULL);

	pthread_mutex_unlock(&lol.spoon);
	pthread_mutex_unlock(&lol.voice);

	pthread_create(&un, NULL, &ft_philo, &lol);
	lol.i = 1;
	pthread_create(&deux, NULL, &ft_philo, &lol);

	pthread_join(un, (void *)&lol);
	pthread_join(deux, (void *)&lol);

	pthread_mutex_destroy(&lol.spoon);
	pthread_mutex_destroy(&lol.voice);
}