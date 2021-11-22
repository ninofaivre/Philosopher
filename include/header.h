/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 17:19:26 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/22 15:49:00 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <stdbool.h>
# include <pthread.h>

typedef struct s_philo_data
{
	pthread_mutex_t	fork;
	struct s_env	*env;
	int				id;
	long long int	last_eat;
	int				n_eat;
}	t_philo_data;

typedef struct s_env
{
	bool				end;
	long long int		start_time;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_eat;
	int					n_philo;
	pthread_mutex_t		message;
	struct s_philo_data	*philo_data;
}	t_env;

int				atoi_mod(char *str);
long long int	get_ms(void);
void			msleep(long long int ms);
void			message(t_env *env, int id, char *str);

void			eat(t_env *env, int id);
void			think(t_env *env, int id);
void			slumber(t_env *env, int id);

void			create_threads_philo(pthread_t *threads, t_env *env);
void			create_and_join_monitor(t_env *env);

#endif