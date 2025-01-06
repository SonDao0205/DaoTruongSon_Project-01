#include "../include/adminAccounts.h"

void adminLoadAccounts(adminAccount accounts[], int *size)
{
    FILE *file;
    file = fopen("data/adminAccounts.bin", "rb");
    if (file == NULL)
    {
        *size = 1;
        strcpy(accounts[0].username, "admin");
        strcpy(accounts[0].password, "admin");
        file = fopen("data/adminAccounts.bin", "wb");
        if (file == NULL)
        {
            printf("Cannot create file!\n");
            return;
        }
        fwrite(size, sizeof(int), 1, file);
        fwrite(accounts, sizeof(adminAccount), *size, file);
        fclose(file);
        return;
    }
    fread(size, sizeof(int), 1, file);
    fread(accounts, sizeof(adminAccount), *size, file);
    fclose(file);
}

int adminLogin(adminAccount accounts[], int size)
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
