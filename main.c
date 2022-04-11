#include <stdio.h>
//#include "structure.h"
#include "functions.c"



int main() {
    char * filename = "users.dat";
    int command;
    int num_of_users = 0;
    user* credits;

    do {
        puts("Enter the command");
        command = enterInt();
        switch (command) {
            case 1:
                credits = realloc(credits, sizeof(user) * ++num_of_users);
                credits[num_of_users - 1] = user_add();
                break;
            case 2:
                print_info(credits, num_of_users);
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
                num_of_users = load(filename, credits);
                break;
            case 6:
                sort_menu(credits, num_of_users);
                break;
            case 7:
                filter(credits, num_of_users);
        }
    } while (command != -1);

    return 0;
}
