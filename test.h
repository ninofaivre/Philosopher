typedef struct s_philo
{
	pthread_mutex_t	fork;
	struct t_struct	*s;
	long long int	last_eating_time;
	int				n_eat;
}	t_philo;

typedef struct s_struct
{
	long long int	start_time;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_eat;
	int				n_philo;
	pthread_mutex_t	message;
	struct s_philo	*philo;
	int				id;
}	t_struct;