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

int main(int ac, char const **av)
{
	t_var	params;

	memset(&params, 0, sizeof(t_var));
	if (!philo_parse_params(&params, ac - 1, av + 1))
	{
		write(STDOUT_FILENO, "Error!\ninvalid params\n", 22);
		return (EXIT_FAILURE);
	}
	if (!philo_init(&params))
	{
		write(STDOUT_FILENO, "Error!\nfailed to allocate enough memory\n", 40);
		return (EXIT_FAILURE);
	}
	philo_start();
	return 0;

}
