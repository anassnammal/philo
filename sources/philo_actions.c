#include "philo.h"


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
