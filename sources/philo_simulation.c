#include "philo.h"

static void	philo_destroy_locks(t_mutex *l, uint64_t n)
{
	uint64_t	i;

	i = 0;
	while (i < n)
	{
		if (pthread_mutex_destroy(l + i))
		{
			perror("pthread mutex destroy");
			break ;
		}
		i++;
	}
}

static void	philo_join(pthread_t *t, uint64_t n)
{
	uint64_t	i;

	i = 0;
	while (i < n)
	{
		if (pthread_join(t[i], NULL))
		{
			perror("pthread join");
			break ;
		}
		i++;
	}
}

static bool	philo_init_locks(t_mutex *l, uint64_t n)
{
	uint64_t	i;

	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init(l + i, NULL))
		{
			perror("pthread mutex init");
			philo_destroy_locks(l, i);
			return (false);
		}
		i++;
	}
	return (true);
}

static void	philo_init(t_philo *p, t_mutex *l, uint64_t n)
{
	uint64_t	i;

	i = 0;
	while (i < n)
	{
		p[i].id = i + 1;
		p[i].last_meal = 0;
		p[i].state = true;
		p[i].right_l = l + i;
		p[i].left_l = (l + (i + 1) % n);
		if (i % 2 == 0)
		{
			p[i].right_l = (l + (i + 1) % n);
			p[i].left_l = l + i;
		}
		p[i].state_l = l + n + i;
		p[i].print_l = l + n * 2;
		i++;
	}
}

void	philo_simulation(t_philo *p, pthread_t *t, t_mutex *l, uint64_t n)
{
	uint64_t	i;

	if (!philo_init_locks(l, n * 2 + 1))
		return ;
	philo_init(p, l, n);
	philo_get_time();
	i = 0;
	while (i < n)
	{
		if (pthread_create(t + i, NULL, philo_routine, p + i))
		{
			perror("pthread create");
			break ;
		}
		i++;
	}
	philo_monitor(p);
	philo_join(t, n);
	philo_destroy_locks(l, n * 2 + 1);
}

