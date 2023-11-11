#include "philo.h"

static bool	philo_parse_params(t_var *params, int c, char const **av)
{
	int	*ptr;

	if (c != 4 && c != 5)
		return (false);
	ptr = &(params->n_philo);
	while (c--)
	{
		ptr[c] = ft_atoi(av[c]);
		if (ptr[c] <= 0)
			return (false);
	}
	return (true);
}

static void	philo_start_simulation()
{
	t_data	*p_data;
	int		i;

	p_data = (t_data *)philo_get(PHILO_DATA_PTR);
	i = 0;
	while (i < p_data->params->n_philo)
	{
		if (pthread_create(p_data->tid + i, NULL, NULL, p_data->philos + i))
		{
			perror("pthread create");
			return ;
		}
		if (!p_data->params->n_meals && pthread_detach(p_data->tid[i]))
		{
			perror("pthread detach");
			return ;
		}
		i++;
	}
}

int main(int ac, char const **av)
{
	t_var		params;
	t_lock	*death_lock;
	bool	*death_flag;

	memset(&params, 0, sizeof(t_var));
	if (!philo_parse_params(&params, ac - 1, av + 1))
		return (EXIT_FAILURE);
	if (!philo_init(&params))
		return (EXIT_FAILURE);
	philo_start_simulation();

	death_flag = (bool *)philo_get(PHILO_DATA_PDF);
	while (true)
	{
		pthread_mutex_lock(death_lock);
		if (*death_flag)
			break ;
		pthread_mutex_unlock(death_lock);
		usleep(100);
	}
	philo_release_res();
	return 0;
}
