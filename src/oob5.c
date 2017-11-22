#include <unistd.h>
#include <sys/fcntl.h>
#include <stdio.h>
#include <string.h>

unsigned int pincode[4] = {0, 11111, 22222, 88888};
char user[4][8] = {"admin", "alice", "bob", "guest"};

void admin_shell() {
    execve("/bin/sh", 0, 0);
}

int main() {
    unsigned long id;
    unsigned int pin;

    setvbuf(stdout, 0, _IONBF, 0);
    printf("Stack Ref = %p\n", &id);

    for (int i = 0; i < 3; ++i) {
        printf("User ID: ");
        scanf("%ld%*c", &id);

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
