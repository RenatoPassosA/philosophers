#include "philo.h"

static bool philo_died(t_philo *philo)
{
	long long   current_time;

	current_time = get_timestamp_ms();
	if ((current_time - get_llong(&philo->philo_mutex, &philo->last_meal_time)) > philo->table->time_to_die)
		return (true);
	return (false);
}

void    monitor(t_table *table)
{
    int         index;
	int			philos_full;

	index = 0;
	while (!simulation_finished(table))
	{
		philos_full = 0;
		//printf("Monitorando...\n");
		if (philo_died(&table->philos[index]))
		{
			printf("MORREU");
			set_bool(&table->table_mutex, &table->end_dinner, true);
			print_status(DIED, &table->philos[index]);
			break;
		}
		if (table->philos[index].is_full)
			philos_full++;
		if (philos_full == table->num_of_philos)
		{
			printf("TODOS CHEIOS");
			set_bool(&table->table_mutex, &table->end_dinner, true);
			break;
		}
		index++;
		if (index == table->num_of_philos - 1)
			index = 0;
		precise_usleep(100, table);	
	}
}
/*




	while (index < table->num_of_philos)
	{
		if (get_bool(&table->philos[index].philo_mutex, &table->philos[index].is_full))
			philos_full++;
		if (get_bool(&table->table_mutex, &table->end_dinner))
			;//limpar tudo
		current_time = get_timestamp_ms();
		if ((current_time - get_llong(&table->philos->philo_mutex, &table->philos[index].last_meal_time)) > table->time_to_die)
		{
			printf("MORREU");
			print_status(DIED, &table->philos[index]);
			//limpar tudo
			break;
		}
		if (philos_full == table->num_of_philos)
		{
			printf("TODOS CHEIOS");
			//limpar tudo e sair
			break;
		}
		printf("Philo %d: last_meal = %lld, now = %lld, diff = %lld\n", index, get_llong(&table->philos[index].philo_mutex, &table->philos[index].last_meal_time), current_time, current_time - get_llong(&table->philos[index].philo_mutex, &table->philos[index].last_meal_time));
		index++;
		if (index == table->num_of_philos)
			index = 0;
		precise_usleep(100, table);		
	}
	exit(EXIT_SUCCESS);
}*/
