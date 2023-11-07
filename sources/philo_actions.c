#include "philo.h"

void		*philo_get(uint8_t option, int i)
{
	static t_philo_vars	philos;

	if (option == LOCK_PTR)
		return (&philos.locks[i]);
	if (option == STATE_PTR)
		return (&philos.state[i - 1]);
	if (option == PLOCK_PTR)
		return (&philos.locks[0]);
	if (option == TEAT_PTR)
		return (philos.params->t_toeat);
	if (option == TSLEEP_PTR)
		return (philos.params->t_tosleep);
	if (option == TDIE_PTR)
		return (philos.params->t_todie);
	if (option == NMEALS_PTR)
		return (philos.params->n_meals);
	return (&philos);
}

void	*philo_life_cycle(void *ptr)
{
	int			philo;
	t_state		*state;
	uint64_t	last_meal;
	uint64_t	now;

	philo = *(int *)ptr;
	state = philo_get(STATE_PTR, philo);

	return (NULL);	
}
