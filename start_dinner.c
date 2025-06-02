#include "philo.h"

void	start_dinner(t_table *table)
{
	int	index;

	index = -1;
	if (table->number_of_meals == 0)
		return ;
	while (++index < table->num_of_philos)
		set_thread(&table->philos[index].thread, routine, &table->philos[index], "CREATE");
	table->start_time = get_timestamp_ms();
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	while(!simulation_finished(table))
		monitor(table);
	index = -1;
	while (++index < table->num_of_philos)
		set_thread(&table->philos[index].thread, NULL, NULL, "JOIN");
	
}
