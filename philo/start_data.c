/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 13:50:57 by rpassos-          #+#    #+#             */
/*   Updated: 2025/06/05 16:24:21 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_timestamp_ms(void)
{
	struct timeval	start_time;

	gettimeofday(&start_time, NULL);
	return ((start_time.tv_sec * 1000) + (start_time.tv_usec / 1000));
}

static void	start_philos(char **av, t_table *table, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		philos[i].thread = 0;
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = table->start_time;
		philos[i].is_dead = false;
		philos[i].is_full = false;
		philos[i].right_fork = 0;
		philos[i].left_fork = 0;
		philos[i].r_fork = &table->forks[(i + 1)
			% table->num_of_philos];
		philos[i].l_fork = &table->forks[i];
		if (philos[i].id % 2 == 0)
		{
			philos[i].r_fork = &table->forks[i];
			philos[i].l_fork = &table->forks[(i + 1) % table->num_of_philos];
		}
		pthread_mutex_init(&philos[i].philo_mutex, NULL);
		philos[i].table = table;
		i++;
	}
}

void	start_table(char **av, t_table *table, t_philo *philos)
{
	int	index;

	index = -1;
	table->num_of_philos = ft_atoll(av[1]);
	table->time_to_die = ft_atoll(av[2]) * 1000;
	table->time_to_eat = ft_atoll(av[3]) * 1000;
	table->time_to_sleep = ft_atoll(av[4]) * 1000;
	if (av[5] && av[5][0])
		table->number_of_meals = ft_atoll(av[5]);
	else
		table->number_of_meals = -1;
	table->start_time = get_timestamp_ms();
	table->end_dinner = false;
	table->all_threads_ready = false;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->num_of_philos);
	if (!table->forks)
	{
		free(philos);
		exit_error_msg("Allocation Failed");
	}
	pthread_mutex_init(&table->table_mutex, NULL);
	pthread_mutex_init(&table->print_action, NULL);
	while (++index < table->num_of_philos)
		pthread_mutex_init(&table->forks[index], NULL);
	start_philos(av, table, philos);
}

void	start_data(t_table *table, char **av)
{
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * ft_atoll(av[1]));
	if (!philos)
		exit_error_msg("Allocation Failed");
	table->philos = philos;
	start_table(av, table, philos);
}
