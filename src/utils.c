/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:09:08 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/22 13:51:05 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include "header.h"
#include <stdio.h>

int	atoi_mod(char *str)
{
	int	to_return;

	to_return = 0;
	if (!str || !*str)
		return (-1);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		to_return *= 10;
		to_return += (int)(*str - '0');
		str++;
	}
	return (to_return);
}

long long int	get_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)));
}

void	msleep(long long int ms)
{
	long long int	ms_start;

	ms_start = get_ms();
	while ((get_ms() - ms_start) < ms)
	{
	}
}

void	message(t_struct *s, int id, char *str)
{
	pthread_mutex_lock(&s->message);
	if (s->end == false)
		printf("%lli %i %s\n", (get_ms() - s->start_time), id, str);
	pthread_mutex_unlock(&s->message);
}
