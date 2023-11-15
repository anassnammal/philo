/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anammal <anammal@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 08:21:29 by anammal           #+#    #+#             */
/*   Updated: 2023/11/15 08:21:59 by anammal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_var		*philo_get_params()
{
	static t_var	params;

	return (&params);
}

static bool	philo_parse_params(int c, char const **av)
{
	uint64_t	*ptr;

	if (c != 4 && c != 5)
		return (false);
	ptr = &(philo_get_params()->n_philo);
	while (c--)
	{
		ptr[c] = philo_atoui64(av[c]);
		if (ptr[c] == 0)
			return (false);
	}
	return (true);
}

int			 main(int ac, char const **av) // need error msg
{
	t_philo		*philos;
	pthread_t	*tids;
	t_mutex		*locks;
	uint64_t	n;

	if (!philo_parse_params(ac - 1, av + 1))
		return (perror("ff"),EXIT_FAILURE);
	n = philo_get_params()->n_philo;
	philos = (t_philo *)malloc(sizeof(t_philo) * n);
	if (!philos)
		return (EXIT_FAILURE);
	tids = (pthread_t *)malloc(sizeof(pthread_t) * n);
	if (!tids)
		return (free(philos), EXIT_FAILURE);
	locks = (t_mutex *)malloc(sizeof(t_mutex) * (n * 2 + 1));
	if (!locks)
		return (free(philos), free(tids), EXIT_FAILURE);
	philo_simulation(philos, tids, locks, n);
	return (free(philos), free(tids), free(locks), 0);
}
