#include <unistd.h>
#include <stdio.h>
#include <inttypes.h>
#include <sys/time.h>

uint64_t	philo_get_time()
{
	static uint64_t	bef_ms;
	uint64_t		now_ms;
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (!bef_ms)
		bef_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	now_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (now_ms - bef_ms);
}

int main(int argc, char const *argv[])
{
    printf("%"PRId64"\n", philo_get_time());
    usleep(200 * 1000);
    printf("%"PRId64"\n", philo_get_time());
    usleep(200 * 1000);
    printf("%"PRId64"\n", philo_get_time());
    usleep(200 * 1000);
    printf("%"PRId64"\n", philo_get_time());
    return 0;
}
