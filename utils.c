/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpassos- <rpassos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 15:56:54 by rpassos-          #+#    #+#             */
/*   Updated: 2025/05/27 18:36:52 by rpassos-         ###   ########.fr       */
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
	if (ft_strcmp(type, "CREATE") == 0)
		pthread_create(thread, NULL, func, NULL);
	else if (ft_strcmp(type, "JOIN") == 0)
		pthread_join(*thread, NULL);
	else if (ft_strcmp(type, "DETACH") == 0)
		pthread_detach(*thread);
}// criar o handle de error