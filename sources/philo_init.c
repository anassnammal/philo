#include "philo.h"

static bool philo_init_mem()
{
	t_data  *philo_data;
	int		n;

	n = philo_data->params->n_philo;
	philo_data = (t_data *)philo_get(PHILO_DATA_PTR);
	philo_data->tid = (pthread_t *)malloc(sizeof(pthread_t) * n);
	if (philo_data->tid == NULL)
		return (false);
	philo_data->locks = (t_lock *)malloc(sizeof(t_lock) * (n + 2));
	if (philo_data->locks == NULL)
		return (free(philo_data->tid), false);
	philo_data->philos = (t_philo *)malloc(sizeof(t_philo) * n);
	if (philo_data->philos == NULL)
		return (free(philo_data->tid), free(philo_data->locks), false);
	return (true);
}

static bool	philo_init_mtx()
{
	t_lock	*locks;
	int		n;
	int		i;

	locks = (t_lock *)philo_get(PHILO_DATA_MTX);
	n = ((t_var *)philo_get(PHILO_DATA_PRM))->n_philo + 2;
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(locks + i, NULL))
		{
			perror("pthread mutex init");
			return (false);
		}
		i++;
	}
	return (true);
}

static void	philo_init_ptrs()
{
	t_data	*philo_data;
	int		i;
	int		n;

	philo_data = (t_data *)philo_get(PHILO_DATA_PTR);
	i = 0;
	n = philo_data->params->n_philo;
	while (i < n)
	{
		philo_data->philos[i].id = i + 1;
		philo_data->philos[i].count_meal = philo_data->params->n_meals;
		philo_data->philos[i].last_meal = 0;
		philo_data->philos[i].is_dead = &philo_data->is_dead;
		philo_data->philos[i].right = philo_data->locks + i;
		philo_data->philos[i].left = philo_data->locks + (i + 1) % n;
		if (!(i % 2))
		{
			philo_data->philos[i].right = philo_data->locks + (i + 1) % n;
			philo_data->philos[i].left = philo_data->locks + i;
		}
		philo_data->philos[i].params = philo_data->params;
		i++;
	}
}

bool philo_init(t_var *params)
{
	t_data  *philo_data;

	philo_data = (t_data *)philo_get_data();
	philo_data->params = params;
	philo_data->is_dead = false;
	if (!philo_init_mem())
		return (philo_err("malloc err"), false);
	if (!philo_init_mtx())
		return (false);
	return (philo_init_ptrs(), true);
}

void *philo_get(uint8_t op)
{
    static t_data philo_data;

	if (op & PHILO_DATA_TID)
		return (philo_data.tid);
	if (op & PHILO_DATA_MTX)
		return (philo_data.locks);
	if (op & PHILO_DATA_PRM)
		return (philo_data.params);
	if (op & PHILO_DATA_PHL)
		return (philo_data.philos);
	if (op & PHILO_DATA_PDF)
		return (&philo_data.is_dead);
	if (op & PHILO_DATA_PPM)
		return (&philo_data.locks[philo_data.params->n_philo]);
	if (op & PHILO_DATA_PDM)
		return (&philo_data.locks[philo_data.params->n_philo + 1]);
    return (&philo_data);
}