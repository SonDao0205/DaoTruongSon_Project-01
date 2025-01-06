#include "../include/teacherAccounts.h"

void teacherLoadAccounts(teacherAccount accounts[], int *accountSize)
{
    FILE *file;
    file = fopen("data/teacherAccounts.bin", "rb");
    if (file == NULL)
    {
        *accountSize = 0;
        return;
    }
    fread(accountSize, sizeof(int), 1, file);
    fread(accounts, sizeof(teacherAccount), *accountSize, file);
    fclose(file);
}

void teacherSaveAccounts(teacherAccount accounts[], int size)
{
    FILE *file;
    file = fopen("data/teacherAccounts.bin", "wb");
    if (file == NULL)
    {
        printf("Cannot open file to write!\n");
        return;
    }
    fwrite(&size, sizeof(int), 1, file);
    fwrite(accounts, sizeof(teacherAccount), size, file);
    fclose(file);
}

int teacherLogin(teacherAccount accounts[], int size)
{
    char username[100];
    char password[100];
    printf("Username: ");
    getchar();
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';
    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';
    for (int i = 0; i < size; i++)
    {
        if (strcmp(accounts[i].username, username) == 0 && 
            strcmp(accounts[i].password, password) == 0)
        {
            return 1;
        }
    }
    return 0;
}

void teacherRegisterAccount(teacherAccount accounts[], int *size)
{
    teacherAccount newAccount;
    printf("Username : ");
    getchar();
    fgets(newAccount.username, sizeof(newAccount.username), stdin);
    newAccount.username[strcspn(newAccount.username, "\n")] = '\0';
    printf("Password: ");
    fgets(newAccount.password, sizeof(newAccount.password), stdin);
    newAccount.password[strcspn(newAccount.password, "\n")] = '\0';
    accounts[*size] = newAccount;
    (*size)++;
    teacherSaveAccounts(accounts, *size);
    printf("Register success!\n");
}