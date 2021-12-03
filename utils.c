#include "philo.h"

long	get_timestamp(void)
{
	static long start = 0;
	long 		time;
	struct timeval tv;

	time = 0;
	if (gettimeofday(&tv, NULL))
		return (-1);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (start == 0)
		 start = time; 
	time = time - start;
	return (time);
}

/////////////////MAY CAUSE OFFSET/////////////////////
long	ft_usleep(long usec)
{
	long long	start;
	long long	time;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	start = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	time = 0;	
	while (time < usec)
	{
		gettimeofday(&tv, NULL);
		time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000) - start;
		usleep(50);
	}
	return (time);
}

