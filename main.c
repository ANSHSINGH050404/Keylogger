#include <stdio.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Usage: %s <event-file>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    struct input_event ie;

    ssize_t bytes = read(fd, &ie, sizeof(ie));

    if (bytes != sizeof(ie)) {
        perror("read");
        close(fd);
        return 1;
    }

    printf("Event type: %u\n", ie.type);
    printf("Event code: %u\n", ie.code);
    printf("Event value: %d\n", ie.value);

    close(fd);

    return 0;
}
