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

void	philo_destroy_mutex(t_lock *lock, int last)
{
	int		i;

	i = 0;
	while (i < last)
	{
		if (pthread_mutex_destroy(lock + i))
		{
			perror("ERROR!\npthread mutex destroy");
			break ;
		}
		i++;
	}
}

bool	philo_init(t_philo *ph, t_lock *lock, t_var *p)
{
	int	i;

	i = -1;
	while (++i < p->n_philo)
	{
		ph->id = i + 1;
		ph->state = THINKING;
		ph->right = lock + i;
		ph->left = lock + (i + 1) % p->n_philo;
		ph->print = lock + p->n_philo;
		ph->params = p;
		if (pthread_mutex_init(lock + i, NULL))
		{
			perror("ERROR!\npthread mutex init");
			return (philo_destroy_mutex(lock, i), false);
		}
	}
	if (pthread_mutex_init(lock + i, NULL))
	{
		perror("ERROR!\npthread mutex init");
		return (philo_destroy_mutex(lock, i), false);
	}
	return (true);
}

int main(int ac, char const **av)
{
	t_var		params;
	pthread_t	*tid;
	t_lock		*locks;
	t_philo		*philo;

	memset(&params, 0, sizeof(t_var));
	if (!philo_parse_params(&params, ac - 1, av + 1))
		return (EXIT_FAILURE);
	tid = (pthread_t *)malloc(sizeof(pthread_t) * params.n_philo);
	if (!tid)
		return (EXIT_FAILURE);
	locks = (t_lock *)malloc(sizeof(t_lock) * params.n_philo + 1);
	if (!locks)
		return (free(tid), EXIT_FAILURE);
	philo = (t_philo *)malloc(sizeof(t_philo) * params.n_philo);
	if (!philo)
		return (free(tid), free(locks), NULL);
	if (!philo_init(philo, locks, &params))
		return (EXIT_FAILURE);
	philo_start();
	return 0;

}
