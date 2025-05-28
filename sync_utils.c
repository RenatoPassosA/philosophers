#include "philo.h"

void    wait_threads_creation(t_table *table)
{
    while (!get_bool(&table->table_mutex, &table->all_threads_ready))
        continue;
}