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
	long long					num_of_philos;
	long long					time_to_die;
	long long					time_to_eat;
	long long					time_to_sleep;
	long long					number_of_meals;
	long long					start_time;
	bool						end_dinner;
	bool						all_threads_ready;
	pthread_mutex_t				*forks;
	pthread_mutex_t				print_action;
	pthread_mutex_t				table_mutex;
	t_philo						*philos;
		
}				t_table;
typedef struct s_philo
{
	pthread_t				thread;
    long long				id;
    long long				meals_eaten;
    long long				last_meal_time;
    bool					is_dead; 
	bool					is_full;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
	pthread_mutex_t			philo_mutex;
	t_table					*table;
}				t_philo;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_RIGHT_FORK,
	TAKE_LEFT_FORK,
	DIED,
}			t_philo_status;

long long	ft_atoll(char *s);
void		*routine(void *arg);
long long	get_timestamp_ms(void);
void		exit_error_msg(char *str);
void		start_dinner(t_table *table);
bool		check_args(int ac, char **av);
int			ft_strcmp(char *s1, char *s2);
bool		simulation_finished(t_table *table);
void		wait_threads_creation(t_table *table);
void    	start_data(t_table *table, char **av);
void		precise_usleep(long usec, t_table *table);
bool		get_bool(pthread_mutex_t *mutex, bool *value);
long long   get_llong(pthread_mutex_t *mutex, bool *value);
void	    print_status(t_philo_status status, t_philo *philo);
void		set_bool(pthread_mutex_t *mutex, bool *dest, bool value);
void    	set_llong(pthread_mutex_t *mutex, long long  *dest, long long  value);
void		set_thread(pthread_t *thread, void *(*func)(void *), void *data, char *type);

#endif