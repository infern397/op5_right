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
        curChar = getchar();
        int len_change = 0; // Определяет, на сколько изменится длина массива
        int length_dif = 0;
        // Если мы ситраем символы, а не пишем их,
        if (curChar == BACKSPACE_KEY)
        {
            len_change = -1; // то будем уменьшать длину массива
            length_dif = 1; // и копировать строку до предпоследнего символа
        }
            // Иначе проверяем, входит ли введённый символ в диапазон печатных
        else
        {
            if (curChar >= START_CHAR_RANGE && curChar <= END_CHAR_RANGE)
            {
                len_change = 1; // Если да, то будем увеличиватьдлину на 1
                length_dif = 2; // Не заполняем последние 2 символа -
                // оставлем мето для введённого символа и \0
            }
            else
                continue; // Если это не печатный символ, то пропускаем его
        }
        // Если стирать больше нечего, но пользователь всё равно жмёт Backspace,
        int newSize = curSize + len_change;
        if (newSize == 0)
            continue; // то мы переходим на следующую итерацию - ждём '\n'

        char* tmpStr = (char*)malloc(newSize * sizeof(char));

        // Идём до предпоследнего символа, т.к. надо в конец записать 0
        for (int i = 0; i < newSize - length_dif; ++i)
            tmpStr[i] = userStr[i];
        if (curChar != BACKSPACE_KEY) // Если введён печатный символ,
            tmpStr[newSize - 2] = curChar; // Добавляем его в строку
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
        perror("Error occured while opening file");
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
        printf("ha");

    }
    fclose(fp);
    return 0;
}

int load(char * filename) {
    FILE * fp;
    char *c;
    int m = sizeof(int);
    int n, i;

    int *pti = (int *)malloc(m);

    if ((fp = fopen(filename, "r")) == NULL)
    {
        perror("Error occured while opening file");
        return 1;
    }

    c = (char *)pti;

    while (m>0)
    {
        i = getc(fp);
        if (i == EOF) break;
        *c = i;
        c++;
        m--;
    }

    n = *pti;

    user* credits = malloc(n * sizeof(user));
    c = (char *) credits;
    // после записи считываем посимвольно из файла
    while ((i= getc(fp))!=EOF)
    {
        *c = i;
        c++;
    }

    printf("%s", *c);

    printf("%d", n);
    return 0;
}