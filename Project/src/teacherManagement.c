#include "../include/teacherManagement.h"

void loadTeachers(Teacher teachers[], int *size, FILE *file)
{
    file = fopen("data/teacher.bin", "rb");
    if (file == NULL)
    {
        *size = 0;
        return;
    }
    fread(size, sizeof(int), 1, file);
    fread(teachers, sizeof(Teacher), *size, file);
    fclose(file);
}

void saveTeachers(Teacher teachers[], int size, FILE *file)
{
    file = fopen("data/teacher.bin", "wb");
    if (file == NULL)
    {
        printf("Cannot open file to write!\n");
        return;
    }
    fwrite(&size, sizeof(int), 1, file);
    fwrite(teachers, sizeof(Teacher), size, file);
    fclose(file);
}

void displayTeachers(Teacher teachers[], int size)
{
    if (size == 0)
    {
        printf("Empty Teacher list!\n");
        return;
    }
    printf("======== Teacher Management =======\n\n");
    printf("|===========|=====================|===================================|=================|\n");
    printf("|    ID     |        Name         |            Email                  |    Phone        |\n");
    printf("|===========|=====================|===================================|=================|\n");
    for (int i = 0; i < size; i++)
    {
        printf("|%-11s|%-21s|%-35s|%-17s|\n", teachers[i].id, teachers[i].name, teachers[i].email, teachers[i].phone);
        printf("|-----------|---------------------|-----------------------------------|-----------------|\n");
    }
    backMenu();
}

void displayInformationTeachers(Teacher teachers[], int size, char searchID[100])
{
    for (int i = 0; i < strlen(searchID); i++)
    {
        searchID[i] = toupper(searchID[i]);
    }
    printf("Teacher Information : \n");
    for (int i = 0; i < size; i++)
    {
        if (strcmp(searchID, teachers[i].id) == 0)
        {
            printf("ID : %s\n", teachers[i].id);
            printf("Name : %s\n", teachers[i].name);
            printf("Email : %s\n", teachers[i].email);
            printf("Phone Number : %s\n", teachers[i].phone);
        }
    }
}

void addTeacher(Teacher teachers[], int *size, FILE *file)
{
    if (*size >= 100)
    {
        printf("The teacher list is full!\n");
        return;
    }
    Teacher newTeacher;
    while (1)
    {
        printf("Enter ID: ");
        getchar();
        fgets(newTeacher.id, sizeof(newTeacher.id), stdin);
        newTeacher.id[strcspn(newTeacher.id, "\n")] = '\0';
        int flag = 0;
        for (int i = 0; i < *size; i++)
        {
            if (strcmp(newTeacher.id, teachers[i].id) == 0)
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
    fgets(newTeacher.name, sizeof(newTeacher.name), stdin);
    newTeacher.name[strcspn(newTeacher.name, "\n")] = '\0';
    while (1)
    {
        printf("Enter email: ");
        fgets(newTeacher.email, sizeof(newTeacher.email), stdin);
        newTeacher.email[strcspn(newTeacher.email, "\n")] = '\0';
        int flag = 0;
        for (int i = 0; i < *size; i++)
        {
            if (strcmp(newTeacher.email, teachers[i].email) == 0)
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
        fgets(newTeacher.phone, sizeof(newTeacher.phone), stdin);
        newTeacher.phone[strcspn(newTeacher.phone, "\n")] = '\0';
        int flag = 0;
        for (int i = 0; i < *size; i++)
        {
            if (strcmp(newTeacher.phone, teachers[i].phone) == 0)
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
    teachers[*size] = newTeacher;
    (*size)++;
    saveTeachers(teachers, *size, file);
    printf("Add teacher success!\n");
    backMenu();
}

void editTeacher(Teacher teachers[], int size, FILE *file)
{
    Teacher updateTeachers;
    char searchID[100];
    printf("Enter ID: ");
    getchar();
    fgets(searchID, 100, stdin);
    searchID[strcspn(searchID, "\n")] = '\0';
    for (int i = 0; i < strlen(searchID); i++)
    {
        searchID[i] = toupper(searchID[i]);
    }
    for (int i = 0; i < size; i++)
    {
        char temp[100];
        strcpy(temp, teachers[i].id);
        for (int i = 0; i < strlen(temp); i++)
        {
            temp[i] = toupper(temp[i]);
        }
        if (strcmp(temp, searchID) == 0)
        {
            displayInformationTeachers(teachers, size, searchID);
            printf("===== Edit A Teacher =====\n");
            printf("Enter new name: ");
            fgets(teachers[i].name, sizeof(teachers[i].name), stdin);
            teachers[i].name[strcspn(teachers[i].name, "\n")] = '\0';
            while (1)
            {
                printf("Enter new email: ");
                fgets(updateTeachers.email, sizeof(updateTeachers.email), stdin);
                updateTeachers.email[strcspn(updateTeachers.email, "\n")] = '\0';
                int flag = 0;
                for (int i = 0; i < size; i++)
                {
                    if (strcmp(updateTeachers.email, teachers[i].email) == 0)
                    {
                        flag = 1;
                        printf("Error : Email already exists!\n");
                        break;
                    }
                    else
                    {
                        strcpy(teachers[i].email, updateTeachers.email);
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
                fgets(updateTeachers.phone, sizeof(updateTeachers.phone), stdin);
                updateTeachers.phone[strcspn(updateTeachers.phone, "\n")] = '\0';
                int flag = 0;
                for (int i = 0; i < size; i++)
                {
                    if (strcmp(updateTeachers.phone, teachers[i].phone) == 0)
                    {
                        flag = 1;
                        printf("Error : Phone number already exists!\n");
                        break;
                    }
                    else
                    {
                        strcpy(teachers[i].phone, updateTeachers.phone);
                    }
                }
                if (flag == 0)
                {
                    break;
                }
            }
            saveTeachers(teachers, size, file);
            printf("Edit teacher success!\n");
            backMenu();
            return;
        }
    }
    printf("No teacher found!\n");
    backMenu();
}

void deleteTeacher(Teacher teachers[], int *size, FILE *file)
{
    char searchID[100];
    printf("Enter ID: ");
    getchar();
    fgets(searchID, 100, stdin);
    searchID[strcspn(searchID, "\n")] = '\0';
    for (int i = 0; i < strlen(searchID); i++)
    {
        searchID[i] = toupper(searchID[i]);
    }
    for (int i = 0; i < *size; i++)
    {
        char temp[100];
        strcpy(temp, teachers[i].id);
        for (int i = 0; i < strlen(temp); i++)
        {
            temp[i] = toupper(temp[i]);
        }
        if (strcmp(temp, searchID) == 0)
        {
            char x;
            displayInformationTeachers(teachers, *size, searchID);
            printf("===== Delete A Teacher =====\n");
            printf("Are you sure want to delete this teacher?(Y/N) : ");
            scanf("%c", &x);
            x = toupper(x);
            switch (x)
            {
            case 'Y':
                for (int j = i; j < *size - 1; j++)
                {
                    teachers[j] = teachers[j + 1];
                }
                (*size)--;
                saveTeachers(teachers, *size, file);
                printf("Teacher delete success!\n");
                backMenu();
                break;
            case 'N':
                printf("Teacher delete failed !\n");
                backMenu();
                break;
            default:
                printf("Invalid choice!\n");
                backMenu();
                break;
            }
        }
    }
    printf("No teacher found!\n");
}

void searchTeacher(Teacher teachers[], int size)
{
    char searchName[100];
    printf("Enter name: ");
    getchar();
    fgets(searchName, 100, stdin);
    searchName[strcspn(searchName, "\n")] = '\0';
    for (int i = 0; i < strlen(searchName); i++)
    {
        searchName[i] = toupper(searchName[i]);
    }
    int flag = 0;
    for (int i = 0; i < size; i++)
    {
        char temp[100];
        strcpy(temp, teachers[i].name);
        for (int i = 0; i < strlen(temp); i++)
        {
            temp[i] = toupper(temp[i]);
        }
        if (strstr(temp, searchName) != NULL)
        {
            printf("\nTeacher Information : \n");
            printf("ID : %s\n", teachers[i].id);
            printf("Name : %s\n", teachers[i].name);
            printf("Email : %s\n", teachers[i].email);
            printf("Phone number : %s\n", teachers[i].phone);
            flag = 1;
        }
    }
    if (flag == 0)
    {
        printf("No teacher found!\n");
    }
    backMenu();
}

void AddClassroomForTeacher(Classroom classrooms[],Teacher teachers[],int classroomSize,int teacherSize){
    char searchTeacherId[100];
    char searchClassId[100];
    int classIndex;
    int teacherIndex;
    int flag;
    printf("Enter Teacher ID : ");
    getchar();
    fgets(searchTeacherId,100,stdin);
    searchTeacherId[strcspn(searchTeacherId, "\n")] = '\0';  
    for (int i = 0; i < strlen(searchTeacherId); i++)
    {
        searchTeacherId[i] = toupper(searchTeacherId[i]);
    }
    flag = 0;
    for (int i = 0; i < teacherSize; i++)
    {
        if (strcmp(searchTeacherId,teachers[i].id) == 0)
        {
            teacherIndex = i;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("No teacher found!\n");
        return;
    }
    printf("Enter Classroom ID : ");
    fgets(searchClassId,100,stdin);
    searchClassId[strcspn(searchClassId, "\n")] = '\0';  
    for (int i = 0; i < strlen(searchClassId); i++)
    {
        searchClassId[i] = toupper(searchClassId[i]);
    }
    flag = 0;
    for (int i = 0; i < classroomSize; i++)
    {
        if (strcmp(searchClassId,classrooms[i].id) == 0)
        {
            classIndex = i;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("No Classroom found!\n");
        return;
    }
    if (classrooms[classIndex].status == 1) {
        printf("This classroom already has a teacher.!\n");
        return;
    }
    strcpy(classrooms[classIndex].teacherId, teachers[teacherIndex].id);
    classrooms[classIndex].status = 1;
    printf("Add teacher to classroom successfully!\n");
}
