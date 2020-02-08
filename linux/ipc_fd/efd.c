#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>      
#include <sys/eventfd.h>
#include <sys/shm.h> 
#include <sys/socket.h>
#include <sys/ipc.h> 
#include "send_fd.h"

int main()
{
	int	sv[2];
	int efd[2]={0,0};
	uint64_t ui, uo;

	if (socketpair(AF_LOCAL, SOCK_STREAM, 0, sv) < 0) {
		perror("socketpair");
		exit(1);
	}

	if(fork() == 0) {
		// child
		close(sv[0]);

		efd[0] = recv_fd(sv[1]);
		efd[1] = recv_fd(sv[1]);
		printf("received fds %d %d\n", efd[0], efd[1]);
		
		while(1) {
			eventfd_read(efd[0], &ui);
			
			printf("efd1 = %llx\n", ui);

			eventfd_write(efd[1], 1);
		}
	} else {
		// parent
		close(sv[1]);
		efd[0] = eventfd(1, EFD_SEMAPHORE);
		efd[1] = eventfd(0, EFD_SEMAPHORE);

		printf("send fds %d %d \n", efd[0], efd[1]);
		send_fd(sv[0], efd[0]);
		send_fd(sv[0], efd[1]);

		while (1) {
			eventfd_read(efd[1], &uo);
			
			printf("efd2 = %llx\n", uo);
			
			usleep(1000000);

			eventfd_write(efd[0], 1);
		}

	}

	return 0;
}