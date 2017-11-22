#include <unistd.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <string.h>

void admin_shell() {
    execve("/bin/sh", 0, 0);
}

int main() {
    unsigned int pincode[4] = {0, 11111, 22222, 88888};
    char user[4][8] = {"admin", "alice", "bob", "guest"};

    setvbuf(stdout, 0, _IONBF, 0);

    for (int i = 0; i < 3; ++i) {
        int id;
        unsigned int pin;
        printf("User ID: ");
        scanf("%d%*c", &id);
        if (id >= 4) {
            puts("non-existed ID!\n");
            continue;
        }
        printf("Nickname: ");
        fgets(user[id], 8, stdin);
        user[id][strcspn(user[id], "\n")] = 0;
        printf("PIN: ");
        scanf("%u", &pin);

        printf("Logging as [%s] ... ", user[id]);
        if (pin == pincode[id]) {
            puts("Ok!\n");
            puts("## Nothing here ##");
            return 0;
        } else {
            puts("Failed\nIncorrect PIN code!\n");
        }
    }
    return 0;
}
