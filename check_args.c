#include "philo.h"

long long	ft_atoll(char *s)
{
	long long int	result;
	int				minus_sign;

	minus_sign = 0;
	result = 0;
	while (*s)
	{
		while (*s == 32 || (*s >= 9 && *s <= 13))
			s++;
		if (*s == '+' || *s == '-')
		{
			if (*s == '-')
				minus_sign = 1;
			s++;
		}
		while (*s >= '0' && *s <= '9')
		{
			result = result * 10 + (*s - '0');
			s++;
		}
		if (minus_sign)
			return (result * -1);
		return (result);
	}
	return (0);
}

bool	is_only_num(char *str)
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

bool	check_args(int ac, char **av)
{
	int	index;

	index = 1;
	if (ac < 4 || ac > 5)
		return (false);
	while (index < ac)
	{
		if (!is_only_num(av[index]))
			return (false);
		index++;
	}
	index = 1;
	while (index < ac - 1)
	{
		if (ft_atoll(av[index]) <= 0)
			return (false);
		index++;
	}
	if (av[5] && ft_atoll(av[5]) < 0)
		return (false);
	return (true);
}
