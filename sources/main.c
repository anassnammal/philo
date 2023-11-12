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

static bool	philo_start_simulation()
{
	t_data	*d;
	int		i;

	d = (t_data *)philo_get(PHILO_DATA_PTR);
	i = 0;
	while (i < d->params->n_philo)
	{
		if (pthread_create(&d->tid[i], NULL, philo_routine, &d->philos[i]))
		{
			perror("pthread create");
			return (false);
		}
		if (pthread_detach(d->tid[i]))
		{
			perror("pthread detach");
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	philo_died(t_philo *p, uint64_t now)
{
	bool	is_dead;

	is_dead = false;
	pthread_mutex_lock(philo_get(PHILO_LOCK_LML));
	if (now - p->last_meal >= (uint64_t)p->params->t_todie)
	{
		is_dead = true;
		philo_print(p, now, M_DIE);
	}
	pthread_mutex_unlock(philo_get(PHILO_LOCK_LML));
	return (is_dead);
}

static bool	philo_finished(t_philo *p)
{
	bool	is_finished;

	is_finished = false;
	pthread_mutex_lock(philo_get(PHILO_LOCK_MCT));
	if (p->count_meal == p->params->n_meals)
		is_finished = true;
	pthread_mutex_unlock(philo_get(PHILO_LOCK_MCT));
	return (is_finished);
}

int main(int ac, char const **av)
{
	t_var		params;
	t_philo		*philos;
	int			c;
	int			i;

	memset(&params, 0, sizeof(t_var));
	if (!philo_parse_params(&params, ac - 1, av + 1))
		return (EXIT_FAILURE);
	if (!philo_init(&params))
		return (EXIT_FAILURE);
	philo_start_simulation();
	philos = philo_get(PHILO_DATA_PHL);
	i = 0;
	c = 0;
	while (true)
	{
		if (philo_died(philos + i, philo_get_time()))
			break ;
		c += philo_finished(philos + i);
		if (c == params.n_meals)
			break ;
		i++;
		if (i == params.n_philo)
			i = 0;
	}
	return (philo_release_res(), 0);
}
