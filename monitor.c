#include "philo.h"

void    monitor(t_table *table)
{
    int index;

    index = -1;
    if (get_bool(&table->philos->philo_mutex, &table->philos->is_full))
    {
        //limpar tudo
        exit(EXIT_SUCCESS);
    }
    if (get_bool(&table->table_mutex, &table->end_dinner))
        ;//limpar tudo
    while (++index < table->philos)
    {}
    

}
