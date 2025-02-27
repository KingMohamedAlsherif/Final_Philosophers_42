/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malsheri <malsheri@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 09:46:45 by malsheri          #+#    #+#             */
/*   Updated: 2025/02/26 09:46:46 by malsheri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(const char *text)
{
	if (*text && (*text == '+'))
		text++;
	if (*text == '\0')
		return (0);
	while (*text)
	{
		if (*text < '0' || *text > '9')
			return (0);
		text++;
	}
	return (1);
}

void	write_string(char *text, int output)
{
	int	i;

	if (!text)
		return ;
	i = 0;
	while (text[i])
	{
		write(output, &text[i], 1);
		i++;
	}
}

long	convert_to_number(const char *text)
{
	int		i;
	int		polarity;
	long	value;

	i = 0;
	polarity = 1;
	value = 0;
	while (text[i] && ((text[i] >= 9 && text[i] <= 13) || text[i] == 32))
		i++;
	if (text[i] && (text[i] == '+' || text[i] == '-'))
	{
		if (text[i] == '-')
			polarity = -1;
		i++;
	}
	while (text[i] && (text[i] >= '0' && text[i] <= '9'))
	{
		if (polarity == -1 && value * 10 < value)
			return (0);
		else if (polarity == 1 && value * 10 < value)
			return (-1);
		value = (value * 10) + (text[i] - '0');
		i++;
	}
	return (value * polarity);
}

size_t	current_timestamp(void)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == -1)
		write(2, "timestamp error\n", 16);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

int	delay_execution(size_t duration)
{
	size_t	begin;

	begin = current_timestamp();
	while ((current_timestamp() - begin) < duration)
		usleep(500);
	return (0);
}
