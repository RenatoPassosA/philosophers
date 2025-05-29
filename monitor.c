#include "philo.h"

void    monitor(t_table *table)
{
    int         index;
    long long   current_time;

    index = 0;
    current_time = get_timestamp_ms();
    if (get_bool(&table->philos->philo_mutex, &table->philos->is_full))
    {
        //limpar tudo
        exit(EXIT_SUCCESS);
    }
    if (get_bool(&table->table_mutex, &table->end_dinner))
        ;//limpar tudo
    while (index <= table->num_of_philos)
    {
        if (current_time - table->philos[index].last_meal_time > table->time_to_die)
        {
            print_status(DIED, &table->philos[index]);
            //limpar tudo
        }
        if (index == table->num_of_philos)
            index = 0;
    }

    //philo[0] - id 1
    

}
