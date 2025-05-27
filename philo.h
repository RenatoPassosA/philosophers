#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <limits.h>

typedef struct s_philo t_philo;

typedef struct s_table
{
	int					num_of_philos;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_meals;
	long long			start_time;
	long long			end_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_action;
	t_philo				*philos;
		
}				t_table;
typedef struct s_philo
{
	pthread_t				thread;
    int						id;
    int						meals_eaten;
    long long				last_meal_time;
    bool					is_dead; 
	bool					is_full;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
	t_table					*table;
}				t_philo;


long long	ft_atoll(char *s);
long long	get_timestamp_ms(void);
void		exit_error_msg(char *str);
bool		check_args(int ac, char **av);
void    	start_data(t_table *table, char **av);
int			ft_strcmp(char *s1, char *s2);

#endif