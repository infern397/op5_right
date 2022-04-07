#include <stdio.h>
//#include "structure.h"
#include "functions.c"



int main() {
    char * filename = "users.dat";
    int command = 1;
    int num_of_users = 1;
    user* credits = calloc(1, sizeof(user));

    do {
        puts("Enter the command");
        command = enterInt();
        switch (command) {
            case 1:
                credits[num_of_users - 1] = user_add();
                credits = realloc(credits, sizeof(user) * ++num_of_users);
                break;
            case 2:
                print_info(credits, num_of_users - 1);
                break;
            case 3:
                fputs("Enter the number\n", stdout);
                command = enterInt();
                if (command != -1) {
                    user_del(credits, command - 1, num_of_users);
                    num_of_users--;
                    printf("12");
                }
                break;
            case 4:
                save(filename, credits, num_of_users);
                break;
            case 5:
                load(filename);
                break;
        }
    } while (command != -1);

    return 0;
}
