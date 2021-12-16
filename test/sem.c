#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
int main(void)
{
	sem_t *sem;

	sem_unlink("/ft_forks");
	sem = sem_open("/ft_forks", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 10);
	for (int i = 0; i < 90; i++)
		sem_post(sem);
	for (int i = 0; i < 101; i++)
		sem_wait(sem);

	sem_close(sem);
	sem_unlink("/ft_forks");
	return 0;
}