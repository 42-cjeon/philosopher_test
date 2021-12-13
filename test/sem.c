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
	
	sem = sem_open("forks", O_CREAT | O_EXCL, S_IRUSR | S_IWUSR, 10);

	sem_close(sem);
	sem_unlink("forks");
	return 0;
}