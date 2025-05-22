#include "philo.h"

static void	mutex_print(t_philo *philo, char *action)
{
	if (ft_strncmp(action, "eating") == 0)
	{
		pthread_mutex_lock(&philo->table->print_action);
		printf("%ld %d is eating", get_timestamp_ms(), philo->id);
		pthread_mutex_unlock(&philo->table->print_action);
	}
	else if (ft_strncmp(action, "sleeping") == 0)
	{
		pthread_mutex_lock(&philo->table->print_action);
		printf("%ld %d is sleeping", get_timestamp_ms(), philo->id);
		pthread_mutex_unlock(&philo->table->print_action);
	}
	else if (ft_strncmp(action, "thinking") == 0)
	{
		pthread_mutex_lock(&philo->table->print_action);
		printf("%ld %d is thinking", get_timestamp_ms(), philo->id);
		pthread_mutex_unlock(&philo->table->print_action);
	}
	else if (ft_strncmp(action, "taken a fork") == 0)
	{
		pthread_mutex_lock(&philo->table->print_action);
		printf("%ld %d has taken a fork", get_timestamp_ms(), philo->id);
		pthread_mutex_unlock(&philo->table->print_action);
	}
}

static void	lock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_fork);
		mutex_print(philo, "taken a fork");
		pthread_mutex_lock(philo->r_fork);
		mutex_print(philo, "taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		mutex_print(philo, "taken a fork");
		pthread_mutex_lock(philo->l_fork);
		mutex_print(philo, "taken a fork");
	}
}

static void	unlock_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	
}

void	routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (1)
	{
		if (philo->is_dead == 1 || philo->meals_eaten == philo->number_of_meals)
			break;
		usleep(100);
		lock_forks(philo);
		mutex_print(philo, "eating");
		usleep(philo->time_to_eat * 1000);
		philo->meals_eaten++;
		unlock_forks(philo);
		mutex_print(philo, "sleeping");
		usleep(philo->time_to_sleep * 1000);
		mutex_print(philo, "thinking");
	}
	return ;
}
