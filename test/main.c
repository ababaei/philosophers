#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include "adder.h"

void *adder(void *data)
{
	t_int *ret;

	ret = data;
	pthread_mutex_lock(&ret->mtx);
	while (ret->ret < 100)
		ret->ret += 10;
	pthread_mutex_unlock(&ret->mtx);
}

int main(void)
{
	t_int	ret;
	pthread_t	thread;

	ret.ret = 0;

	pthread_mutex_init(&ret.mtx, NULL);
	pthread_create(&thread, NULL, adder, &ret);

	pthread_mutex_lock(&ret.mtx);
	ret.ret += 3;
	pthread_mutex_unlock(&ret.mtx);
	pthread_join(thread, NULL);
	printf("ret = %d\n", ret.ret);
	return (ret.ret);
}
