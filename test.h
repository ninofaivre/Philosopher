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