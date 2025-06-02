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

	/*printf("now: %lld, last meal: %lld, diff: %lld\n", current_time, last_meal, diff);
	printf("time_to_die: %lld\n", philo->table->time_to_die);*/

	if (diff > philo->table->time_to_die / 1000 && !get_bool(&philo->philo_mutex, &philo->is_full))
	{
		printf("------------------------------------chegou\n");
		
		return (true);
	}
	return (false);
}

void    monitor(t_table *table)
{
    int         index;
	int			philos_full;
	//long long   current_time;


	

	index = 0;
	while (!simulation_finished(table))
	{
		//current_time = get_timestamp_ms();
		
		//printf("Monitorando...\n");
		if (philo_died(&table->philos[index]))
		{
			printf("MORREU\n");
			print_status(DIED, &table->philos[index]);
			check_forks(table->philos);
			set_bool(&table->table_mutex, &table->end_dinner, true);
			break;
		}
		if (get_bool(&table->philos[index].philo_mutex, &table->philos[index].is_full))
			philos_full++;
		//printf("%d\n", philos_full);
		if (philos_full == table->num_of_philos)
		{
			printf("TODOS CHEIOS\n");
			set_bool(&table->table_mutex, &table->end_dinner, true);
			break;
		}
		//printf("Philo %d: last_meal = %lld, now = %lld, diff = %lld\n", index, get_llong(&table->philos[index].philo_mutex, &table->philos[index].last_meal_time), current_time, current_time - get_llong(&table->philos[index].philo_mutex, &table->philos[index].last_meal_time));
		index++;
		if (index == table->num_of_philos)
		{
			index = 0;
			philos_full = 0;
		}
		precise_usleep(1, table);	
	}
}
