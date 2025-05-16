#include "philo.h"

static long long	get_start_timestamp(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	return ((start_time.tv_sec * 1000LL) + (start_time.tv_usec / 1000));
}

void    start_table(char **av, t_table *table)
{
    int index;

    index = -1;
    table->num_of_philos = ft_atoll(av[1]);
    table->start_time = get_start_timestamp();
    table->forks = malloc(sizeof(pthread_mutex_t) * table->num_of_philos);
    if (!table->forks)
        return ;
    table->philos = malloc(sizeof(t_philo) * table->num_of_philos);
    if (!table->philos)
    {
        if (table->forks)
            free(table->forks);
        return ;
    }
    while (++index < table->num_of_philos)
        pthread_mutex_init(&table->forks[index], NULL);
}

void    start_philos(char **av, t_table *table, t_philo *philos)
{
    int index;

    index = 0;
    while (index < table->num_of_philos)
    {
        philos[index].id = index + 1;
        philos[index].actual_action = 0;
        philos[index].meals_eaten = 0;
        philos[index].last_meal = 0;
        philos[index].is_dead = 0;
        philos[index].l_fork = &table->forks[index];
        philos[index].r_fork = &table->forks[(index + 1) % table->num_of_philos];
        philos[index].time_to_die = ft_atoll(av[2]);
        philos[index].time_to_eat = ft_atoll(av[3]);
        philos[index].time_to_sleep  = ft_atoll(av[4]);
        if (av[5] && av[5][0])
            philos[index].number_of_meals = ft_atoll(av[5]);
        else
            philos[index].number_of_meals = -1;
        index++;
    }
}

void    start_data(char **av)
{
    t_table table;

    start_table(av, &table);
    start_philos(av, &table, table.philos);
}
