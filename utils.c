/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:56:54 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/28 16:44:20 by rpassos-         ###   ########.fr       */
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

void	set_thread(pthread_t *thread, void *(*func)(void *), void *data, char *type)
{
	int	ret;
	
	if (ft_strcmp(type, "CREATE") == 0)
	{
		ret = pthread_create(thread, NULL, func, NULL);
		if (ret)
		{
			//destruir todos os threads criados até agora
			exit_error_msg("Thread creation failed.\n");
		}
	}
	else if (ft_strcmp(type, "JOIN") == 0)
		pthread_join(*thread, NULL);
	else if (ft_strcmp(type, "DETACH") == 0)
		pthread_detach(*thread);
}

void	precise_usleep(long usec, t_table *table)
{
	long	start;
	long	now;

	start = get_timestamp_ms();
	while (1)
	{
		if (get_bool(&table->end_dinner, &table->end_dinner))
			break;
		now = get_timestamp_ms();
		if ((now - start) * 1000 >= usec)
			break;
		usleep(100);
	}
}