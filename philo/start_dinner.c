/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:55:42 by rpassos-          #+#    #+#             */
/*   Updated: 2025/06/05 17:26:03 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_dinner(t_table *table)
{
	int	index;

	index = -1;
	if (table->number_of_meals == 0)
	{
		clean_all(table);
		return ;
	}
	while (++index < table->num_of_philos)
		set_thread(&table->philos[index], routine, table, "CREATE");
	table->start_time = get_timestamp_ms();
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	while (!simulation_finished(table))
		monitor(table);
	index = -1;
	while (++index < table->num_of_philos)
		set_thread(&table->philos[index], NULL, NULL, "JOIN");
	clean_all(table);
}

void	print_status(t_philo_status status, t_philo *philo)
{
	long long	elapsed;

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
	else if (status == DIED)
		printf("%-6lld %lld died\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->table->print_action);
}
