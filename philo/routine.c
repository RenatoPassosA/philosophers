/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:52:22 by rpassos-          #+#    #+#             */
/*   Updated: 2025/06/05 17:40:05 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_threads_creation(t_table *table)
{
	while (!get_bool(&table->table_mutex, &table->all_threads_ready))
	{
		usleep(1);
		continue ;
	}
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	set_llong(&philo->philo_mutex, &philo->right_fork, 1);
	print_status(TAKE_RIGHT_FORK, philo);
	pthread_mutex_lock(philo->l_fork);
	set_llong(&philo->philo_mutex, &philo->left_fork, 1);
	print_status(TAKE_LEFT_FORK, philo);
	set_llong(&philo->philo_mutex, &philo->last_meal_time, get_timestamp_ms());
	philo->meals_eaten++;
	print_status(EATING, philo);
	precise_usleep(philo->table->time_to_eat, philo->table);
	if (philo->table->number_of_meals > 0
		&& philo->meals_eaten == philo->table->number_of_meals)
		set_bool(&philo->philo_mutex, &philo->is_full, true);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	set_llong(&philo->philo_mutex, &philo->right_fork, 0);
	set_llong(&philo->philo_mutex, &philo->left_fork, 0);
}

static void	one_philo(t_philo *philo)
{	
	pthread_mutex_lock(philo->r_fork);
	set_llong(&philo->philo_mutex, &philo->right_fork, 1);
	print_status(TAKE_RIGHT_FORK, philo);
	precise_usleep(philo->table->time_to_die, philo->table);
	return ;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_threads_creation(philo->table);
	while (!simulation_finished(philo->table))
	{
		if (get_bool(&philo->philo_mutex, &philo->is_full))
			break ;
		if (philo->table->num_of_philos == 1)
		{
			one_philo(philo);
			break ;
		}
		else
			eat(philo);
		print_status(SLEEPING, philo);
		precise_usleep(philo->table->time_to_sleep, philo->table);
		print_status(THINKING, philo);
		usleep(1);
	}
	if (get_llong(&philo->philo_mutex, &philo->right_fork) == 1)
		pthread_mutex_unlock(philo->r_fork);
	if (get_llong(&philo->philo_mutex, &philo->left_fork) == 1)
		pthread_mutex_unlock(philo->l_fork);
	return (NULL);
}
