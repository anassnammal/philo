#include "philo.h"

static void	philo_destroy_mutex(uint64_t last)
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

static void	philo_detach_thread(uint64_t last)
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

static void	philo_join_thread(uint64_t last)
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

static void	philo_launch_threads()
{
	t_philos	*philos;
	uint64_t	i;

	philos = philo(GET_PHILOS_PTR);
	i = 0;
	while (i < philos->params->n_philo)
	{
		if (pthread_create(philos->philos + i, NULL, NULL, ((void *)i)))
		{
			philo_detach_thread(i);
			philo(RELEASE_ALL);
			break ;
		}
		i++;
	}
}

t_philos	*philo(uint8_t operation)
{
	static t_philos	philos;

	if (operation & LAUNCH_PHILOS)
		philo_launch_threads();
	if (operation & JOIN_PHILOS)
		philo_join_thread(philos.params->n_philo);
	if (operation & DESTROY_FORKS)
		philo_destroy_mutex(philos.params->n_philo);
	if (operation & DETACH_PHILOS)
		philo_detach_thread(philos.params->n_philo);
	if (operation & DESTROY_PRINT)
		pthread_mutex_destroy(&(philos.print));
	if (operation & RELEASE_MEMORY)
		(free(philos.philos), free(philos.forks));
	if (operation & CLEAR_STCVAR)
		memset(&philos, 0, sizeof(t_philos));
	return (&philos);
}
