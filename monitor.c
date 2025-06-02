#include "philo.h"

static void	check_forks(t_philo *philo)
{
	int	index;

	index = 0;
	while (index < philo->table->num_of_philos)
	{
		if (philo[index].right_fork == 1)
		{
			set_llong(&philo->philo_mutex, &philo->right_fork, 0);	
			pthread_mutex_unlock(philo->r_fork);
		}
		if (philo[index].left_fork == 1)
		{
			set_llong(&philo->philo_mutex, &philo->left_fork, 0);
			pthread_mutex_unlock(philo->l_fork);
		}
		set_bool(&philo[index].philo_mutex, &philo[index].is_full, true);
		index++;
	}
}

static bool philo_died(t_philo *philo)
{
	long long current_time;
	long long last_meal;
	long long diff;

	current_time = get_timestamp_ms();
	last_meal = get_llong(&philo->philo_mutex, &philo->last_meal_time);
	diff = current_time - last_meal;

	if (diff > philo->table->time_to_die / 1000 && !get_bool(&philo->philo_mutex, &philo->is_full))
		return (true);
	return (false);
}

static void check_reset_index(t_table *table, int *index, int *philos_full)
{
	if (*index == table->num_of_philos)
	{
		*index = 0;
		*philos_full = 0;
	}
}

void    monitor(t_table *table)
{
    int         index;
	int			philos_full;

	index = 0;
	philos_full = 0;
	while (!simulation_finished(table))
	{
		if (philo_died(&table->philos[index]))
		{
			print_status(DIED, &table->philos[index]);
			check_forks(table->philos);
			set_bool(&table->table_mutex, &table->end_dinner, true);
			break;
		}
		if (get_bool(&table->philos[index].philo_mutex, &table->philos[index].is_full))
			philos_full++;
		if (philos_full == table->num_of_philos)
		{
			set_bool(&table->table_mutex, &table->end_dinner, true);
			break;
		}
		index++;
		check_reset_index(table, &index, &philos_full);
		precise_usleep(1, table);	
	}
}
