/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:19:26 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/20 17:20:08 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

typedef struct s_philo
{
	pthread_mutex_t	fork;
	struct s_struct	*s;
	int				id;
	long long int	last_eating_time;
	int				n_eat;
}	t_philo;

typedef struct s_struct
{
	bool			end;
	long long int	start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_eat;
	int				n_philo;
	pthread_mutex_t	message;
	struct s_philo	*philo;
}	t_struct;

int				atoi_mod(char *str);
long long int	get_ms(void);
void			msleep(long long int ms);

void			message(t_struct *s, int id, char *str);
void			eat(t_struct *s, int id);
void			think(t_struct *s, int id);
void			dodo(t_struct *s, int id);

void			create_threads_philo(pthread_t *threads, t_struct *s);
void			*ft_philo(void *arg);

void			*ft_monitor(void *arg);
void			create_and_join_monitor(t_struct *s);

#endif