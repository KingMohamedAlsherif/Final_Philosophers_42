/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:43:10 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/27 13:15:15 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	check_max_min(char *str)
// {
// 	int			si;
// 	long long	res;

// 	res = 0;
// 	si = 1;
// 	while (*str == ' ' || *str == '\t')
// 		str++;
// 	if (*str == '-' || *str == '+')
// 	{
// 		if (*str == '-')
// 			si = -1;
// 		str++;
// 	}
// 	while (*str >= '0' && *str <= '9')
// 	{
// 		res = res * 10 + (*str - '0');
// 		if (si == 1 && res > INT_MAX)
// 			return (0);
// 		else if (si == -1 && (-res) < INT_MIN)
// 			return (0);
// 		str++;
// 	}
// 	return (1);
// }

// int	check_philo_args(char **av)
// {
// 	int	i;

// 	i = 1;
// 	if (ft_atol(av[i]) > 200 || ft_atol(av[i]) < 1)
// 		return (0);
// 	while (av[++i])
// 	{
// 		if (!check_max_min(av[i]) || ft_atol(av[i]) < 1)
// 			return (0);
// 	}
// 	return (1);
// }

// static int	is_space(char c)
// {
// 	if (c == ' ' || c == '\t' || c == '\n'
// 		|| c == '\v' || c == '\f' || c == '\r')
// 		return (1);
// 	return (0);
// }

// const char	*valid_input(const char *str)
// {
// 	int			len;
// 	const char	*num;

// 	len = 0;
// 	while (is_space(*str))
// 		++str;
// 	if (*str == '+')
// 		++str;
// 	else if (*str == '-')
// 		erroring("INPUT ONLY POSITIVE NUMBERS!");
// 	while (!is_digit(*str))
// 		erroring("INPUT ONLY DIGITS!");
// 	num = str;
// 	while (is_digit(*str))
// 	{
// 		str++;
// 		len++;
// 	}
// 	if (len > 10)
// 		erroring("INT_MAX IS THE LIMIT!");
// 	return (num);
// }

// void	erroring(char *str)
// {
// 	write(2, str, strlen(str));
// 	exit(1);
// }


static int	verify_numbers(int count, char **values)
{
	int	i;

	i = 1;
	while (i < count)
	{
		if (!is_number(values[i]))
		{
			write_string("Error: Invalid number: ", STDERR_FILENO);
			write_string(values[i], STDERR_FILENO);
			write_string("\n", STDERR_FILENO);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_config(t_config *config)
{
	if (config->total_philos > 200)
	{
		write_string("Error: Too many philos (max 200)\n", STDERR_FILENO);
		return (1);
	}
	if (config->time_to_starve < 60)
	{
		write_string("Error: Starvation time must be > 60\n", STDERR_FILENO);
		return (1);
	}
	if (config->time_to_consume < 60)
	{
		write_string("Error: Eating time must be > 60\n", STDERR_FILENO);
		return (1);
	}
	if (config->time_to_sleep < 60)
	{
		write_string("Error: Rest time must be > 60\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	process_arguments(int count, char **values, t_config *config)
{
	if (count != 5 && count != 6)
	{
		write_string("Usage: ", STDERR_FILENO);
		write_string(values[0], STDERR_FILENO);
		write_string(" philos starve_time eat_time rest_time [meal_quota]\n",
			STDERR_FILENO);
		return (1);
	}
	if (!verify_numbers(count, values))
		return (1);
	config->total_philos = convert_to_number(values[1]);
	config->time_to_starve = convert_to_number(values[2]);
	config->time_to_consume = convert_to_number(values[3]);
	config->time_to_sleep = convert_to_number(values[4]);
	config->meal_quota = (count == 6) ? convert_to_number(values[5]) : -1;
	return (check_config(config));
}
