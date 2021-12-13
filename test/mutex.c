#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *task(void *k)
{
	usleep(1000);
	write(1, "greetingsgreetingsgreetingsgreetingsgreetingsgreetingsgreetingsgreetingsgreetingsgreetingsgreetingsgreetingsgreetingsgreetingsgreetingsgreetingsgreetingsgreetings\n", 163);

	return (NULL);
}

int main(void)
{
	int fork;
	pthread_t threads[100];

	for (int i = 0; i < 100; i++)
		if (pthread_create(threads + i, NULL, task, NULL))
			exit(100);
	for (int i = 0; i < 100; i++)
		if (pthread_join(threads[i], NULL))
			exit(110);
	return 0;
}