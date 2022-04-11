#include <stdlib.h>
#include <string.h>
#include "structure.h"

#define BACKSPACE_KEY 8
#define START_CHAR_RANGE 32
#define END_CHAR_RANGE 126

char* enterStr()
{
    char* userStr = (char*)calloc(1, sizeof(char));
    userStr[0] = '\0';
    char curChar = 0;
    int curSize = 1;

    while(curChar != '\n')
    {
        curChar = (char) getchar();
        int len_change;
        int length_dif;
        if (curChar == BACKSPACE_KEY)
        {
            len_change = -1;
            length_dif = 1;
        }
        else
        {
            if (curChar >= START_CHAR_RANGE && curChar <= END_CHAR_RANGE)
            {
                len_change = 1;
                length_dif = 2;
            }
            else
                continue;
        }
        int newSize = curSize + len_change;
        if (newSize == 0)
            continue;

        char* tmpStr = (char*)malloc(newSize * sizeof(char));

        for (int i = 0; i < newSize - length_dif; ++i)
            tmpStr[i] = userStr[i];
        if (curChar != BACKSPACE_KEY)
            tmpStr[newSize - 2] = curChar;
        tmpStr[newSize - 1] = '\0';
        free(userStr);
        userStr = tmpStr;
        curSize = newSize;


    }
    return userStr;
}

int enterInt() {
    int num;
    if (scanf("%d", &num)) return num;
    return -1;
}


user user_add() {
    user user_add;
    fputs("Enter the full name\n", stdout);
    fflush(stdin);
    user_add.full_name = enterStr();
    if (user_add.full_name[0] != '\0') {
        fputs("Enter the loan amount\n", stdout);
        user_add.loan_amount = enterInt();
        fputs("Enter the percent\n", stdout);
        user_add.percent = enterInt();
        fputs("Enter the loan term\n", stdout);
        user_add.loan_term = enterInt();
        user_add.amount_of_interest = (user_add.loan_amount * (1 + user_add.percent) - user_add.loan_amount)
                / 100 * user_add.loan_term;
        user_add.monthly_payment_amount = (user_add.loan_amount * ((1 + user_add.percent)) / 100) / user_add.loan_term;
        return user_add;
    }
}

void print_info(user* credit, int users_num) {
    for (int i = 0; i < users_num; i++) {
        printf("Number %d\n", i + 1);
        printf("Full name: %s\n", credit[i].full_name);
        printf("Loan amount: %d\n", credit[i].loan_amount);
        printf("Percent: %d\n", credit[i].percent);
        printf("Loan term: %d\n", credit[i].loan_term);
        printf("Amount of interests: %d\n", credit[i].amount_of_interest);
        printf("Monthly payment: %d\n\n", credit[i].monthly_payment_amount);
    }
}

void user_del(user* credit, int del_num, int users_num) {
    memmove(&credit[del_num], &credit[del_num + 1], (users_num - del_num) * sizeof(user));
}

int save(char* filename, user* credit, int users_num) {
    FILE* fp;
    char* c;

    if ((fp = fopen(filename, "wb")) == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    c = (char *) &users_num;
    for (int i = 0; i < sizeof(int); i++)
    {
        putc(*c++, fp);
    }

    c = (char *) credit;
    for (int i = 0; i < sizeof(user) * users_num; i++)
    {
        putc(*c, fp);
        c++;
    }
    fclose(fp);
    return 0;
}

int load(char * filename, user* users_list) {
    FILE * fp;
    char *c;
    int m = sizeof(int);
    int n, i;
    int *pti = (int *)malloc(m);

    if ((fp = fopen(filename, "r")) == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    c = (char *)pti;

    while (m>0)
    {
        i = getc(fp);
        if (i == EOF) break;
        *c = (char) i;
        c++;
        m--;
    }

    n = *pti;
    users_list = malloc(n * sizeof(user));

    c = (char *) users_list;
    while ((i= getc(fp))!=EOF)
    {
        *c = (char) i;
        c++;
    }

    return n;
}

void sort_info() {
    fputs("1 - Long name\n", stdout);
    fputs("2 - Loan amount\n", stdout);
    fputs("3 - Percent\n", stdout);
    fputs("4 - Loan term\n", stdout);
    fputs("5 - Amount of interest\n", stdout);
    fputs("6 - Monthly_payment_amount\n", stdout);
};

void name_sort(user* users_list, int num_of_users) {
    for (int i = 0; i < num_of_users - 1; i++) {
        for (int e = i; e < num_of_users - i - 1; e++) {
            if (strcmp(users_list[e].full_name, users_list[e + 1].full_name) > 0) {
                user tmp = users_list[e];
                users_list[e] = users_list[e + 1];
                users_list[e + 1] = tmp;
            }
        }
    }
}

void loan_sort(user* users_list, int num_of_users) {
    for (int i = 0; i < num_of_users - 1; i++) {
        for (int e = i; e < num_of_users - i - 1; e++) {
            if (users_list[e].loan_amount > users_list[e + 1].loan_amount) {
                user tmp = users_list[e];
                users_list[e] = users_list[e + 1];
                users_list[e + 1] = tmp;
            }
        }
    }
}

void percent_sort(user* users_list, int num_of_users) {
    for (int i = 0; i < num_of_users - 1; i++) {
        for (int e = i; e < num_of_users - i - 1; e++) {
            if (users_list[e].percent > users_list[e + 1].percent) {
                user tmp = users_list[e];
                users_list[e] = users_list[e + 1];
                users_list[e + 1] = tmp;
            }
        }
    }
}

void term_sort(user* users_list, int num_of_users) {
    for (int i = 0; i < num_of_users - 1; i++) {
        for (int e = i; e < num_of_users - i - 1; e++) {
            if (users_list[e].loan_term > users_list[e + 1].loan_term) {
                user tmp = users_list[e];
                users_list[e] = users_list[e + 1];
                users_list[e + 1] = tmp;
            }
        }
    }
}

void interest_sort(user* users_list, int num_of_users) {
    for (int i = 0; i < num_of_users - 1; i++) {
        for (int e = i; e < num_of_users - i - 1; e++) {
            if (users_list[e].amount_of_interest > users_list[e + 1].amount_of_interest) {
                user tmp = users_list[e];
                users_list[e] = users_list[e + 1];
                users_list[e + 1] = tmp;
            }
        }
    }
}

void payment_sort(user* users_list, int num_of_users) {
    for (int i = 0; i < num_of_users - 1; i++) {
        for (int e = i; e < num_of_users - i - 1; e++) {
            if (users_list[e].monthly_payment_amount > users_list[e + 1].monthly_payment_amount) {
                user tmp = users_list[e];
                users_list[e] = users_list[e + 1];
                users_list[e + 1] = tmp;
            }
        }
    }
}

int name_filter(user* filt_list, int num) {
    puts("Left name");
    fflush(stdin);
    char* left_name = enterStr();
    puts("Right name");
    char *right_name = enterStr();
    for (int i = 0; i < num; i++) {
        if ((strcmp(filt_list[i].full_name, left_name) < 0) || (strcmp(filt_list[i].full_name, right_name) > 0)) {
            memmove(&filt_list[i], &filt_list[i + 1], (num - i) * sizeof(user));
            num--;
        }
    }
    return num;
}

int amount_filter(user* filt_list, int num) {
    puts("Left amount and right amount");
    int left_amount = enterInt();
    int right_amount = enterInt();

    puts("Left amount and right amount");
    for (int i = 0; i < num; i++) {
        if (filt_list[i].loan_amount < left_amount || filt_list[i].loan_amount > right_amount) {
            memmove(&filt_list[i], &filt_list[i + 1], (num - i) * sizeof(user));
            num--;
        }
    }
    return (num);
}

void filter(user* users_list, int num_of_users) {
    int n;
    user* filter_list = malloc(sizeof(user) * num_of_users);
    for (int i = 0; i < num_of_users; i++) {
        filter_list[i] = users_list[i];
    }
    fputs("1 - name\n2 - amount\n3 - percent\n4 - term\n5 - interests\n6 - payment\n", stdout);
    do {
        n = enterInt();
        switch (n) {
            case 1:
                num_of_users = name_filter(filter_list, num_of_users);
                print_info(filter_list, num_of_users);
                break;
            case 2:
                num_of_users = amount_filter(filter_list, num_of_users);
                print_info(filter_list, num_of_users);
        }
    } while (n != 0);

}

void sort_menu(user* list, int users) {
    int sort_choice;
    sort_info();
    sort_choice = enterInt();
    switch (sort_choice) {
        case 1:
            name_sort(list, users);
            break;
        case 2:
            loan_sort(list, users);
            break;
        case 3:
            percent_sort(list, users);
            break;
        case 4:
            term_sort(list, users);
            break;
        case 5:
            interest_sort(list, users);
            break;
        case 6:
            payment_sort(list, users);
            break;
    }
}

