// cc -o led_switch_toggle_native led_switch_toggle_native.c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(void) {
    int fd;
    char buf[4] = {0};
    ssize_t bytes_read, bytes_written;

    fd = open("/dev/led_switch_driver", O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "driver open fail: %s\n", strerror(errno));
        return -1;
    }

    for (int i = 0; i < 20; ++i) {
        bytes_read = read(fd, buf, 4);
        if (bytes_read != 4) {
            fprintf(stderr, "read error: %s\n", strerror(errno));
            close(fd);
            return -1;
        }

        printf("sw1: %d, sw2: %d, sw3: %d, sw4: %d\n", buf[0], buf[1], buf[2], buf[3]);

        bytes_written = write(fd, buf, 4);
        if (bytes_written != 4) {
            fprintf(stderr, "write error: %s\n", strerror(errno));
            close(fd);
            return -1;
        }

        sleep(1);
    }

    close(fd);
    return 0;
}