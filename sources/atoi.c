#include "philo.h"

static int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (*(s + i))
		i++;
	return (i);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n-- > 0)
	{
		if (*(unsigned char *)(s1++) != *(unsigned char *)(s2++))
			return (*(unsigned char *)(--s1) - *(unsigned char *)(--s2));
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	n;
	int	s;

	while (ft_isspace(*str))
		str++;
	s = 1;
	if ((*str == '-' || *str == '+') && ft_isdigit(*(char *)(str + 1)))
		s = 44 - *(str++);
	n = 0;
	if (s == -1 && ft_strlen(str) >= 10 && !ft_isdigit(*(str + 10))
		&& ft_strncmp(str, "2147483648", 10) == 0)
		return (-2147483648);
	while (ft_isdigit(*str))
	{
		n = n * 10 + ((*str) - 48);
		if (n % 10 != (*(str) - 48))
			return ((s == -1) - 1);
		str++;
	}
	return (n * s);
}
