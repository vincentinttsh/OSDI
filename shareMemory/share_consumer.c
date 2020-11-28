#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
int main(){
    const char *name = "OS";  // name of shared memory object
    const int SIZE = 4096;
    int fd;         // shared memory file descriptor
    char *ptr;        // pointer to shared memory object
    int i;
    /* open the shared memory object */
    fd = shm_open(name, O_RDONLY, 0666);
    if (fd == -1) {
        printf("shared memory failed\n");
        exit(-1);
    }
    ptr = (char *) mmap(0,SIZE, PROT_READ, MAP_SHARED,fd, 0);
    if (ptr == MAP_FAILED) {
        printf("Map failed\n");
        exit(-1);
    }
    /* now read from the shared memory object */
    printf("%s", (char *)ptr);
    /* remove the shard memory object */
    if (shm_unlink(name) == -1) {
        printf("Error removing %s\n", name);
        exit(-1);
    }
    return 0;
}

