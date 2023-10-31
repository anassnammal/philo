#include "philo.h"

bool	parse_params(t_var *params, int c, char const **av)
{
	int	*ptr;

	if (c == 4 || c == 5)
	{
		ptr = &(params->n_philo);
		while (c--)
		{
			ptr[c] = ft_atoi(av[c]);
			if (ptr[c] <= 0)
				return (false);
		}
	}
	return (true);
}

t_philos	*init_philos(t_var *params)
{
	static t_philos	philos;
	uint64_t		i;

	if (!params)
		return (&philos);
	philos.philos = (pthread_t *)malloc(sizeof(pthread_t) * params->n_philo);
	if (philos.philos == NULL)
		return (NULL);
	philos.forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * params->n_philo);
	if (philos.forks == NULL)
		return (free(philos.philos), NULL);
	philos.params = params;
	i = 0;
	while (i < params->n_philo)
	{
		if (pthread_mutex_init(&philos.forks[i], NULL))
			return (destroy_forks(i), free(philos.philos), free(philos.forks), NULL);
		i++;
	}
	if (pthread_mutex_init(&philos.print, NULL))
		return (destroy_forks(i), free(philos.philos), free(philos.forks), NULL);
	return (&philos);
}

int main(int ac, char const **av)
{
	t_var	params;

	if (!parse_params(&params, ac - 1, av + 1))
	{
		write(STDOUT_FILENO, "Error!\ninvalid params\n", 22);
		return (EXIT_FAILURE);
	}
	return 0;
}
