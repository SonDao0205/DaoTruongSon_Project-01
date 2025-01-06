#include "../include/studentsManagement.h"

void loadStudents(Student students[], int *size, FILE *file)
{
    file = fopen("data/students.bin", "rb");
    if (file == NULL)
    {
        *size = 0;
        return;
    }
    fread(size, sizeof(int), 1, file);
    fread(students, sizeof(Student), *size, file);
    fclose(file);
}

void saveStudents(Student students[], int size, FILE *file)
{
    file = fopen("data/students.bin", "wb");
    if (file == NULL)
    {
        printf("Cannot open file to write!\n");
        return;
    }
    fwrite(&size, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), size, file);
    fclose(file);
}

void displayStudents(Student students[], int size)
{
    if (size == 0)
    {
        printf("Empty Student list!\n");
        return;
    }
    printf("======== Student Management =======\n\n");
    printf("|===========|=====================|===================================|=================|\n");
    printf("|    ID     |        Name         |            Email                  |    Phone        |\n");
    printf("|===========|=====================|===================================|=================|\n");
    for (int i = 0; i < size; i++)
    {
        printf("|%-11s|%-21s|%-35s|%-17s|\n",students[i].id, students[i].name, students[i].email, students[i].phone);
        printf("|-----------|---------------------|-----------------------------------|-----------------|\n");
    }
    backMenu();
}

void displayInformationStudents(Student students[],int size,char searchID[100])
{
    for (int i = 0; i < strlen(searchID); i++)
    {
        searchID[i] = toupper(searchID[i]);
    }
    printf("Student Information : \n");
    for (int i = 0; i < size; i++)
    {
        if (strcmp(searchID,students[i].id)==0)
        {
            printf("ID : %s\n",students[i].id);
            printf("Name : %s\n",students[i].name);
            printf("Email : %s\n",students[i].email);
            printf("Phone Number : %s\n",students[i].phone);
        }
    }
}

void addStudent(Student students[], int *size, FILE *file)
{
    if (*size >= 100)
    {
        printf("The student list is full!\n");
        return;
    }
    Student newStudent;
    while (1)
    {
        printf("Enter ID: ");
        getchar();
        fgets(newStudent.id,sizeof(newStudent.id),stdin);
        newStudent.id[strcspn(newStudent.id, "\n")] = '\0';
        int flag = 0;
        for (int i = 0; i < *size; i++)
        {
            if (strcmp(newStudent.id,students[i].id)==0)
            {
                flag = 1;
                printf("Error : ID already exists!\n");
                break;
            }
        }
        if (flag == 0)
        {
            break;
        }
    }
    printf("Enter name: ");
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0';
    while (1)
    {
        printf("Enter email: ");
        fgets(newStudent.email,sizeof(newStudent.email),stdin);
        newStudent.email[strcspn(newStudent.email, "\n")] = '\0';
        int flag = 0;
        for (int i = 0; i < *size; i++)
        {
            if (strcmp(newStudent.email,students[i].email)==0)
            {
                flag = 1;
                printf("Error : Email already exists!\n");
                break;
            }
        }
        if (flag == 0)
        {
            break;
        }
    }
    while (1)
    {
        printf("Enter Phone number: ");
        fgets(newStudent.phone,sizeof(newStudent.phone),stdin);
        newStudent.phone[strcspn(newStudent.phone, "\n")] = '\0';
        int flag = 0;
        for (int i = 0; i < *size; i++)
        {
            if (strcmp(newStudent.phone,students[i].phone)==0)
            {
                flag = 1;
                printf("Error : Phone number already exists!\n");
                break;
            }
        }
        if (flag == 0)
        {
            break;
        }
    }
    students[*size] = newStudent;
    students[*size].status = 0;
    (*size)++;
    saveStudents(students, *size, file);
    printf("Add student success!\n");
    backMenu();
}

void editStudent(Student students[], int size, FILE *file)
{
    Student updateStudents;
    char searchID[100];
    printf("Enter ID: ");
    getchar();
    fgets(searchID,100,stdin);
    searchID[strcspn(searchID, "\n")] = '\0';
    for (int i = 0; i < strlen(searchID); i++)
    {
        searchID[i] = toupper(searchID[i]);
    }
    for (int i = 0; i < size; i++)
    {
        char temp[100];
        strcpy(temp,students[i].id);
        for (int i = 0; i < strlen(temp); i++)
        {
            temp[i] = toupper(temp[i]);
        }
        if (strcmp(temp,searchID)==0)
        {
            displayInformationStudents(students,size,searchID);
            printf("===== Edit A Students =====\n");
            printf("Enter new name: ");
            fgets(students[i].name, sizeof(students[i].name), stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0';
            while (1)
            {
                printf("Enter new email: ");
                fgets(updateStudents.email, sizeof(updateStudents.email), stdin);
                updateStudents.email[strcspn(updateStudents.email, "\n")] = '\0';
                int flag = 0;
                for (int i = 0; i < size; i++)
                {
                    if (strcmp(updateStudents.email,students[i].email)==0)
                    {
                        flag = 1;
                        printf("Error : Email already exists!\n");
                        break;
                    }
                    else{
                        strcpy(students[i].email,updateStudents.email);
                    }
                }
                if (flag == 0)
                {
                    break;
                }
            }
            while (1)
            {
                printf("Enter new phone number: ");
                fgets(updateStudents.phone, sizeof(updateStudents.phone), stdin);
                updateStudents.phone[strcspn(updateStudents.phone, "\n")] = '\0';
                int flag = 0;
                for (int i = 0; i < size; i++)
                {
                    if (strcmp(updateStudents.phone,students[i].phone)==0)
                    {
                        flag = 1;
                        printf("Error : Phone number already exists!\n");
                        break;
                    }
                    else{
                        strcpy(students[i].phone,updateStudents.phone);
                    }
                }
                if (flag == 0)
                {
                    break;
                }
            }
            saveStudents(students, size, file);
            printf("Edit student success!\n");
            backMenu();
            return;
        }
    }
    printf("No student found!\n");
    backMenu();
}

void deleteStudent(Student students[], int *size, FILE *file)
{
    char searchID[100];
    printf("Enter ID: ");
    getchar();
    fgets(searchID,100,stdin);
    searchID[strcspn(searchID, "\n")] = '\0';
    for (int i = 0; i < strlen(searchID); i++)
    {
        searchID[i] = toupper(searchID[i]);
    }
    for (int i = 0; i < *size; i++)
    {
        char temp[100];
        strcpy(temp,students[i].id);
        for (int i = 0; i < strlen(temp); i++)
        {
            temp[i] = toupper(temp[i]);
        }
        if (strcmp(temp,searchID)==0)
        {
            char x;
            displayInformationStudents(students,*size,searchID);
            printf("===== Delete A Students =====\n");
            printf("Are you sure want to delete this student?(Y/N) : ");
            scanf("%c",&x);
            x = toupper(x);
            switch (x)
            {
            case 'Y':
                for (int j = i; j < *size - 1; j++)
                {
                    students[j] = students[j + 1];
                }
                (*size)--;
                saveStudents(students, *size, file);
                printf("Student delete success!\n");
                backMenu();
                break;
            case 'N':
                printf("Student delete failed !\n");
                backMenu();
                break;
            default:
                printf("Invalid choice!\n");
                backMenu();
                break;
            }
        }
    }
    printf("No student found!\n");
}
void searchStudent(Student students[], int size)
{
    char searchName[100];
    printf("Enter name: ");
    getchar();
    fgets(searchName,100,stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    for (int i = 0; i < strlen(searchName); i++)
    {
        searchName[i] = toupper(searchName[i]);
    }
    int flag = 0;
    for (int i = 0; i < size; i++)
    {
        char temp[100];
        strcpy(temp,students[i].name);
        for (int i = 0; i < strlen(temp); i++)
        {
            temp[i] = toupper(temp[i]);
        }
        if (strstr(temp,searchName) != NULL)
        {
            printf("\nStudent Information : \n");
            printf("ID : %s\n",students[i].id);
            printf("Name : %s\n",students[i].name);
            printf("Email : %s\n",students[i].email);
            printf("Phone number : %s\n",students[i].phone);
            flag = 1;
        }
    }
    if (flag == 0)
    {
        printf("No student found!\n");
    }
    backMenu();
}

void sortStudents(Student students[], int size)
{
    int choice;
    printf("[1]. Sort ascending by name.\n");
    printf("[2]. Sort descending by name.\n");
    printf("[3]. Exit.\n");
    printf("Enter the choice : ");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (strcmp(students[i].name,students[j].name)>0)
                {
                    Student temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                }
            }
        }
        printf("Student sort success!\n");
        backMenu();
        break;
    case 2:
        for (int i = 0; i < size - 1; i++)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (strcmp(students[i].name,students[j].name)<0)
                {
                    Student temp = students[i];
                    students[i] = students[j];
                    students[j] = temp;
                }
            }
        }
        printf("Student sort success!\n");
        displayStudents(students, size);
        backMenu();
        break;
    case 3:
        break;
    default:
        printf("Invalid choice!\n");
        break;
    }   
}

