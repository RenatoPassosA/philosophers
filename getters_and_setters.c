#include "philo.h"

void    set_bool(pthread_mutex_t *mutex, bool *dest, bool value)
{
    pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

bool    get_bool(pthread_mutex_t *mutex, bool *value)
{
    bool ret;

    pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
    return (value);
}

void    set_llong(pthread_mutex_t *mutex, long long  *dest, long long  value)
{
    pthread_mutex_lock(mutex);
	*dest = value;
	pthread_mutex_unlock(mutex);
}

long long    get_llong(pthread_mutex_t *mutex, bool *value)
{
    long long ret;

    pthread_mutex_lock(mutex);
	ret = *value;
	pthread_mutex_unlock(mutex);
    return (ret);
}

bool    simulation_finished(t_table *table)
{
    return (get_bool(&table->table_mutex, &table->end_dinner));
}