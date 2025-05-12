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
	t_philo				*philos;
	
}				t_table;
typedef struct philo
{
	pthread_t				thread;
    int						id;
    int						actual_action;
    int						meals_eaten;
    long long				last_meal;
    int						is_dead; 
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
	int						time_to_die;
	int						time_to_eat;
	int						time_to_sleep;
	int						number_of_meals;
}				t_philo;




long long	ft_atoll(char *s);

#endif