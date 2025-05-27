#include "philo.h"

long long	get_timestamp_ms(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	return ((start_time.tv_sec * 1000LL) + (start_time.tv_usec / 1000));
}

void    start_philos(char **av, t_table *table, t_philo *philos)
{
    int index;

    index = 0;
    while (index < table->num_of_philos)
    {
        philos[index].id = index + 1;
        philos[index].meals_eaten = 0;
        philos[index].last_meal_time = table->start_time;
        philos[index].is_dead = false;
		philos[index].is_full = false;
        philos[index].l_fork = &table->forks[index];
        philos[index].r_fork = &table->forks[(index + 1) % table->num_of_philos];
        philos[index].table = table;
        index++;
    }
}

void    start_table(char **av, t_table *table, t_philo *philos)
{
    int index;

    index = -1;
    table->num_of_philos = ft_atoll(av[1]);
	table->time_to_die = ft_atoll(av[2]) * 1000;
    table->time_to_eat = ft_atoll(av[3]) * 1000;
    table->time_to_sleep  = ft_atoll(av[4]) * 1000;
	if (av[5] && av[5][0])
		table->number_of_meals = ft_atoll(av[5]);
	else
		table->number_of_meals = -1;
    table->start_time = get_timestamp_ms();
	table->end_time = -1;
    table->forks = malloc(sizeof(pthread_mutex_t) * table->num_of_philos);
    if (!table->forks)
	{
		free(philos);
        exit_error_msg("Allocation Failed");;
	}
    pthread_mutex_init(&table->print_action, NULL);
    while (++index < table->num_of_philos)
        pthread_mutex_init(&table->forks[index], NULL);
    start_philos(av, table, philos);
}

void    start_data(t_table *table, char **av)
{
    t_philo *philos;
    
    philos = malloc(sizeof(t_philo) * ft_atoll(av[1]));
    if (!philos)
        exit_error_msg("Allocation Failed");
    start_table(av, table, philos);
}
