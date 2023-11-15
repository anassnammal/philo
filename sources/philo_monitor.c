#include "philo.h"

static void	philo_died(t_philo *p, uint64_t i, uint64_t now, uint64_t n)
{
	uint64_t	j;

	j = 0;
	while (j < n)
	{
		if (j != i)
			philo_update_state(p + j, false);
		else
			p[i].state = false;
		j++;
	}
	philo_print(p + i, now, M_DIE);
}

void		philo_monitor(t_philo *p)
{
	t_var		*params;
	uint64_t	now;
	uint64_t	i;
	uint64_t	f;

	params = philo_get_params();
	f = 0;
	while (f != params->n_philo)
	{
		f = 0;
		i = 0;
		while (i < params->n_philo)
		{
			pthread_mutex_lock(p[i].state_l);
			now = philo_get_time();
			if (!p[i].state)
				f++;
			else if (now - p[i].last_meal >= params->t_die)
				philo_died(p, i, now, params->n_philo);
			pthread_mutex_unlock(p[i].state_l);
			i++;
		}
	}
}