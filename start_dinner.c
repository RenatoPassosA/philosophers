#include "philo.h"

void	start_dinner(t_table *table)
{
	int	index;

	index = -1;
	if (table->number_of_meals == 0)
		return ;
	else if (table->num_of_philos == 1)
		; //create func
	
	while (++index < table->num_of_philos)
		set_thread(&table->philos[index].thread, routine(), &table->philos[index], "CREATE");
	table->start_time = get_timestamp_ms();
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	index = -1;
	while (++index < table->num_of_philos)
		set_thread(&table->philos[index].thread, NULL, NULL, "JOIN");
}