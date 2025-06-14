/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:51:07 by rpassos-          #+#    #+#             */
/*   Updated: 2025/06/05 14:19:38 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	set_all_philos_full(t_philo *philo)
{
	int	index;

	index = -1;
	while (++index < philo->table->num_of_philos)
		set_bool(&philo[index].philo_mutex, &philo[index].is_full, true);
}

static bool	philo_died(t_philo *philo)
{
	long long	current_time;
	long long	last_meal;
	long long	diff;

	current_time = get_timestamp_ms();
	last_meal = get_llong(&philo->philo_mutex, &philo->last_meal_time);
	diff = current_time - last_meal;
	if (diff > philo->table->time_to_die / 1000
		&& !get_bool(&philo->philo_mutex, &philo->is_full))
		return (true);
	return (false);
}

static void	check_reset_index(t_table *table, int *index, int *philos_full)
{
	if (*index == table->num_of_philos)
	{
		*index = 0;
		*philos_full = 0;
	}
}

void	monitor(t_table *table)
{
	int	i;
	int	philos_full;

	i = 0;
	philos_full = 0;
	while (!simulation_finished(table))
	{
		if (philo_died(&table->philos[i]))
		{
			print_status(DIED, &table->philos[i]);
			set_all_philos_full(table->philos);
			set_bool(&table->table_mutex, &table->end_dinner, true);
			break ;
		}
		if (get_bool(&table->philos[i].philo_mutex, &table->philos[i].is_full))
			philos_full++;
		if (philos_full == table->num_of_philos)
		{
			set_bool(&table->table_mutex, &table->end_dinner, true);
			break ;
		}
		i++;
		check_reset_index(table, &i, &philos_full);
		precise_usleep(1, table);
	}
}
