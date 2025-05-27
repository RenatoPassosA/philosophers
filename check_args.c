#include "philo.h"

long long	ft_atoll(char *s)
{
	long long int	result;
	
	result = 0;
	while (*s)
	{
		while (*s == 32)
			s++;
		while (*s >= '0' && *s <= '9')
		{
			result = result * 10 + (*s - '0');
			s++;
		}
		return (result);
	}
	return (0);
}

static bool	is_only_num(char *str)
{
	if (!*str)
		return (false);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (false);
		str++;
	}
	return (true);
}

static bool	check_value(long long value)
{
	if (value < INT_MIN)
		return(false);
	if (value > INT_MAX)
		return(false);
	if (value < 0)
		return(false);
}

bool	check_args(int ac, char **av)
{
	int	index;

	index = 1;
	if (ac != 5 && ac != 6)
		exit_error_msg("Wrong arguments");
	while (index < ac)
	{
		if (!is_only_num(av[index]))
			exit_error_msg("Only numbers allowed");
		index++;
	}
	index = 1;
	while (index < ac - 1)
	{
		if (check_value(ft_atoll(av[index])))
			exit_error_msg("Args out of correct range");
		index++;
	}
	if (av[5] && ft_atoll(av[5]) < 0)
		exit_error_msg("Number of meals out of correct range");
	return (true);
}
