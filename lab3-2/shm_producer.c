//This file is for producer process using shm_open and mmap.
// gcc sourcecode -o output -lrt
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

int main()
{
	/* the size (in bytes) of shared memory object */
	const int SIZE = 4096;
	/* name of the shared memory object */
	const char *name = "OS";
	/* strings written to shared memory */
	const char *message0 = "Hello";
	const char *message1 = "World!";
	/* shared memory file descriptor */
	int shm_fd;
	/* pointer to shared memory obect */
	void *ptr;
	/* create the shared memory object */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	/* configure the size of the shared memory object */
	ftruncate (shm_fd, SIZE);
	/* memory map the shared memory object */
	ptr = mmap(NULL, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	/* write to the shared memory object */
	sprintf(ptr, "%s", message0);
	ptr += strlen(message0);
	sprintf(ptr,"%s", message1);
	ptr += strlen(message1);
	printf("producing is done.\n");
              return 0;
}
