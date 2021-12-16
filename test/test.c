#include <signal.h>

int main(void)
{
	kill(0, SIGCONT);
	return (0);
}