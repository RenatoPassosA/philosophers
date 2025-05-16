#include "philo.h"

void	routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (1)
	{
		if (philo->id % 2 == 0) //verificar se isso fica
		{
			pthread_mutex_lock(philo->l_fork);
			pthread_mutex_lock(philo->r_fork);
		}
		else
		{
			pthread_mutex_lock(philo->r_fork);
			pthread_mutex_lock(philo->l_fork);
		}

		printf("philo is eating");
		usleep(philo->time_to_eat * 1000);
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		printf("philo is sleeping");
		usleep(philo->time_to_sleep * 1000);
		printf("philo is thinking");

		if (philo->is_dead == 1 || philo->meals_eaten == philo->number_of_meals)
			break;
	}
	return ;
}
