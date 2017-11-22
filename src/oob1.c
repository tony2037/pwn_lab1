#include <unistd.h>
#include <sys/fcntl.h>
#include <stdio.h>

unsigned int pincode[4] = {0, 11111, 22222, 88888};
char user[4][8] = {"admin", "alice", "bob", "guest"};

void set_admin_pincode() {
    int fd = open("/dev/urandom", O_RDONLY);
    unsigned int p;
    read(fd, &p, sizeof(p));
    close(fd);
    pincode[0] = p;
}

int main() {
    setvbuf(stdout, 0, _IONBF, 0);
    set_admin_pincode();

    for (int i = 0; i < 3; ++i) {
        int id;
        unsigned int pin;
        printf("User ID: ");
        scanf("%d", &id);
        if (id >= 4) {
            puts("non-existed ID!\n");
            continue;
        }
        printf("PIN: ");
        scanf("%u", &pin);

        printf("Logging to [%s] ... ", user[id]);
        if (pin == pincode[id]) {
            puts("Ok!\n");
            if (id == 0) {
                execve("/bin/sh", 0, 0);
            } else {
                puts("## Nothing here ##");
            }
            return 0;
        } else {
            puts("Failed\nIncorrect PIN code!\n");
        }
    }
    return 0;
}
