#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/time.h>

typedef struct s_table
{
	int					num_of_philos;
	long long			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_action;
		
}				t_table;
typedef struct philo
{
	pthread_t				thread;
    int						id;
    int						meals_eaten;
    long long				last_meal;
    int						is_dead; 
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						number_of_meals;
	t_table					*table;
}				t_philo;




long long	ft_atoll(char *s);
long long	get_timestamp_ms(void);
int			ft_strcmp(char *s1, char *s2);

#endif