#include "philo.h"

void    print_status(t_philo_status status, t_philo *philo)
{
    long long   elapsed;

    elapsed = get_timestamp_ms() - philo->table->start_time;
    if (philo->is_full)
        return ;
    pthread_mutex_lock(&philo->table->print_action);
	if ((status == TAKE_RIGHT_FORK || status == TAKE_LEFT_FORK) 
        && !simulation_finished(philo->table))
        printf("%-6lld %lld has taken a fork\n", elapsed, philo->id);
    else if (status == EATING && !simulation_finished(philo->table))
        printf("%-6lld %lld is eating\n", elapsed, philo->id);
    else if (status == SLEEPING && !simulation_finished(philo->table))
        printf("%-6lld %lld is sleeping\n", elapsed, philo->id);
    else if (status == THINKING && !simulation_finished(philo->table))
        printf("%-6lld %lld is thinking\n", elapsed, philo->id);
    else if (status == DIED  && !simulation_finished(philo->table))
    {
        printf("%-6lld %lld died\n", elapsed, philo->id);
        set_bool(&philo->table->table_mutex, &philo->table->end_dinner, true);
    }
    pthread_mutex_unlock(&philo->table->print_action);
}
