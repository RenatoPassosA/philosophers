#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stddef.h>
#include <stdbool.h>


typedef struct philo
{
	pthread_t				thread;
    int						id;
    int						actual_action;
    int						meals_eaten;
    long long				last_meal;
    int						is_dead; 
	int						fork[2];
	pthread_mutex_t			mutex;
	t_table					*data;
}	t_philo;


typedef struct s_table
{
	int			total_forks;
	int			number_of_meals;
	int			time_to_die;
	int			time_to_eat;Ñ
	int			time_to_sleep;
	long long	start_time;
} t_table;


#endif