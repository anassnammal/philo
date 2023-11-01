#include "philo.h"

uint64_t	philo_get_time()
{
	struct timeval	time;
	if (gettimeofday(&time, NULL) < 0)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void		philo_print(int i, char const *msg)
{
	t_philos 	*p;
	uint64_t	current_ms;

	current_ms = philo_get_time();
	p = philo(GET_PHILOS_PTR);
	pthread_mutex_lock(&p->print);
	printf("%"PRId64" %d %s\n", current_ms, i, msg);
	pthread_mutex_unlock(&p->print);
}

void		*philo_routine(void *index)
{
	t_philos	*philos;
	t_philo		current;

	philos = philo(GET_PHILOS_PTR);
	current.philo = *((int *)index) + 1;
	if (current.philo % 2)
	{
		current.r_forks = &philos->forks[*((int *)index)];
		current.l_forks = &philos->forks[(*((int *)index) + 1) % philos->params->n_philo];
	}
	else
	{
		current.r_forks = &philos->forks[(*((int *)index) + 1) % philos->params->n_philo];
		current.l_forks = &philos->forks[*((int *)index)];
	}
	current.state = THINKING;
	current.meal_count = philos->params->n_meals;
	current.t_eat = philos->params->t_toeat;
	current.t_sleep = philos->params->t_tosleep;
	current.t_die = philos->params->t_todie;
	philo_life_cycle(&current);
	return (NULL);
}

