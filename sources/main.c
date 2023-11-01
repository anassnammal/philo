#include "philo.h"

static bool	philo_parse_params(t_var *params, int c, char const **av)
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

static bool	philo_init(t_var *params)
{
	t_philos	*philos;
	int			i;

	philos = philo(GET_PHILOS_PTR);
	philos->philos = (pthread_t *)malloc(sizeof(pthread_t) * params->n_philo);
	if (philos->philos == NULL)
		return (philo(CLEAR_STCVAR), false);
	philos->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * params->n_philo);
	if (philos->forks == NULL)
		return (philo(CLEAR_ALL_MEM), false);
	philos->params = params;
	i = 0;
	while (i < params->n_philo)
	{
		if (pthread_mutex_init(&philos->forks[i], NULL))
			return (philo_destroy_mutex(i), philo(CLEAR_ALL_MEM), false);
		i++;
	}
	if (pthread_mutex_init(&philos->print, NULL))
		return (philo(CLEAR_ALL_MEM | DESTROY_FORKS), false);
	return (true);
}

int main(int ac, char const **av)
{
	t_var	params;

	memset(&params, 0, sizeof(t_var));
	if (!philo_parse_params(&params, ac - 1, av + 1))
	{
		write(STDOUT_FILENO, "Error!\ninvalid params\n", 22);
		return (EXIT_FAILURE);
	}
	if (!philo_init(&params))
	{
		write(STDOUT_FILENO, "Error!\nfailed to get enough resources\n", 38);
		return (EXIT_FAILURE);
	}
	philo(RELEASE_ALL | JOIN_PHILOS);
	return 0;
}
