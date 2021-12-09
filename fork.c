/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <student.42seoul.kr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:22:55 by cjeon             #+#    #+#             */
/*   Updated: 2021/12/09 16:46:33 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	int k;

	k = 10;	
	pid = fork();
	if (pid == 0)
	{
		printf("child_process\n");
		usleep(1000000);
		printf("%d\n", k);
	}
	else
	{
		k = 100;
		printf("parents_process\n");
	}
	return 0;
}

/*
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void run(void)
{
	printf("Running...\n");
}

int main(void)
{
	pid_t pids[10];
	pid_t current_pid;
	int status;

	for (int i = 0; i < 10; i++)
	{
		current_pid = fork();
		if (current_pid == 0)
		{
			run();
			exit(0);
		}
		pids[i] = current_pid;
	}
	for (int i = 0; i < 10; i++)
		waitpid(pids[i], &status, 0);
	return 0;
}
*/