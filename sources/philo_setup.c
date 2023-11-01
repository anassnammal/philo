#include "philo.h"

void	philo_destroy_mutex(uint64_t last)
{
	t_philos	*philos;
	uint64_t	i;

	philos = philo(GET_PHILOS_PTR);
	i = 0;
	while (i < last)
	{
		pthread_mutex_destroy(philos->forks + i);
		i++;
	}
}

void	philo_detach_thread(uint64_t last)
{
	t_philos	*philos;
	uint64_t	i;

	philos = philo(GET_PHILOS_PTR);
	i = 0;
	while (i < last)
	{
		pthread_detach(*(philos->philos + i));
		i++;
	}
}

void	philo_join_thread(uint64_t last)
{
	t_philos	*philos;
	uint64_t	i;

	philos = philo(GET_PHILOS_PTR);
	i = 0;
	while (i < last)
	{
		pthread_join(*(philos->philos + i), NULL);
		i++;
	}
}

t_philos	*philo(uint8_t operation)
{
	static t_philos	philos;

	if (operation & LAUNCH_PHILOS)
		philo_launch_threads();
	if (operation & DESTROY_FORKS)
		philo_destroy_mutex(philos.params->n_philo);
	if (operation & DETACH_PHILOS)
		philo_detach_thread(philos.params->n_philo);
	if (operation & JOIN_PHILOS)
		philo_join_thread(philos.params->n_philo);
	return (&philos);
}

bool	philo_init(t_var *params)
{
	t_philos	*philos;
	uint64_t	i;

	if (!params)
		return (NULL);
	philos = philo();
	philos->philos = (pthread_t *)malloc(sizeof(pthread_t) * params->n_philo);
	if (philos->philos == NULL)
		return (NULL);
	philos->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * params->n_philo);
	if (philos->forks == NULL)
		return (free(philos->philos), NULL);
	philos->params = params;
	i = 0;
	while (i < params->n_philo)
	{
		if (pthread_mutex_init(&philos->forks[i], NULL))
			return (philo_forks_destroy(i), free(philos->philos), free(philos->forks), NULL);
		i++;
	}
	if (pthread_mutex_init(&philos->print, NULL))
		return (philo_forks_destroy(i), free(philos->philos), free(philos->forks), NULL);
	return (&philos);
}