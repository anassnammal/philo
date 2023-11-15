/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:22:46 by anammal           #+#    #+#             */
/*   Updated: 2023/11/15 08:22:47 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	philo_atoui64(const char *str)
{
	uint64_t	n;

	n = 0;
	while (*str >= 48 && *str <= 57)
	{
		if ((n * 10 + ((*str) - 48)) % 10 != (uint64_t)(*(str) - 48))
			return (0);
		n = n * 10 + ((*str) - 48);
		str++;
	}
	return (n * (*str == 0));
}

uint64_t	philo_get_time(void)
{
	static uint64_t	first_ms;
	uint64_t		now_ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (!first_ms)
		first_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	now_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (now_ms - first_ms);
}

void	philo_update_state(t_philo	*p, bool new)
{
	pthread_mutex_lock(p->state_l);
	p->state = new;
	pthread_mutex_unlock(p->state_l);
}

bool	philo_state(t_philo *p)
{
	bool	state;

	pthread_mutex_lock(p->state_l);
	state = p->state;
	pthread_mutex_unlock(p->state_l);
	return (state);
}

void	philo_print(t_philo	*p, uint64_t t_ms, char *msg)
{
	pthread_mutex_lock(p->print_l);
	printf("%"PRId64" %"PRId64" %s\n", t_ms, p->id, msg);
	pthread_mutex_unlock(p->print_l);
}
