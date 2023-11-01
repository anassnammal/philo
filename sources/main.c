#include "philo.h"

bool	philo_parse_params(t_var *params, int c, char const **av)
{
	int	*ptr;

	if (c == 4 || c == 5)
	{
		ptr = &(params->n_philo);
		while (c--)
		{
			ptr[c] = ft_atoi(av[c]);
			if (ptr[c] <= 0)
				return (false);
		}
	}
	return (true);
}



int main(int ac, char const **av)
{
	t_var	params;

	if (!parse_params(&params, ac - 1, av + 1))
	{
		write(STDOUT_FILENO, "Error!\ninvalid params\n", 22);
		return (EXIT_FAILURE);
	}
	return 0;
}
