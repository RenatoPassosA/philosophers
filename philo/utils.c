/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:56:54 by rpassos-          #+#    #+#             */
/*   Updated: 2025/06/05 14:18:33 by rpassos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_error_msg(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	set_thread(t_philo *philo, void *(*func)(void *), t_table *table,
		char *type)
{
	pthread_t	*philo_thread;
	int			ret;

	philo_thread = &philo->thread;
	if (ft_strcmp(type, "CREATE") == 0)
	{
		ret = pthread_create(philo_thread, NULL, func, philo);
		if (ret)
		{
			set_bool(&table->table_mutex, &table->end_dinner, true);
			clean_all(philo->table);
			exit_error_msg("Thread creation failed.\n");
		}
	}
	else if (ft_strcmp(type, "JOIN") == 0)
		pthread_join(*philo_thread, NULL);
	else if (ft_strcmp(type, "DETACH") == 0)
		pthread_detach(*philo_thread);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	now;

	start = get_timestamp_ms();
	while (1)
	{
		if (get_bool(&table->table_mutex, &table->end_dinner))
			break ;
		now = get_timestamp_ms();
		if ((now * 1000 - start * 1000) >= usec)
			break ;
		usleep(100);
	}
}

void	clean_all(t_table *table)
{
	int	index;

	index = -1;
	pthread_mutex_destroy(&table->table_mutex);
	pthread_mutex_destroy(&table->print_action);
	while (++index < table->num_of_philos)
	{
		pthread_mutex_destroy(&table->philos[index].philo_mutex);
		pthread_mutex_destroy(&table->forks[index]);
	}
	free(table->forks);
	free(table->philos);
}
