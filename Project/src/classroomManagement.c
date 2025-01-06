#include "../include/classroomManagement.h"

void loadClassroom(Classroom classrooms[], int *size, FILE *file)
{
    file = fopen("data/classroom.bin", "rb");
    if (file == NULL)
    {
        *size = 0;
        return;
    }
    fread(size, sizeof(int), 1, file);
    fread(classrooms, sizeof(Classroom), *size, file);
    fclose(file);
}

void saveClassroom(Classroom classrooms[], int size, FILE *file)
{
    file = fopen("data/classroom.bin", "wb");
    if (file == NULL)
    {
        printf("Cannot open file to write!\n");
        return;
    }
    fwrite(&size, sizeof(int), 1, file);
    fwrite(classrooms, sizeof(Classroom), size, file);
    fclose(file);
}

void displayClassroom(Classroom classrooms[],Teacher teachers[], int classroomSize,int teacherSize)
{
    int teacherIndex;
    int classIndex;
    int flag;
    if (classroomSize == 0)
    {
        printf("Empty Classrooms list!\n");
        return;
    }
    printf("======== Classroom Management =======\n\n");
    printf("|===========|=====================|===================================|=====================|\n");
    printf("|    ID     |        Name         |            Teacher                |  Currently Students |\n");
    printf("|===========|=====================|===================================|=====================|\n");
    for (int i = 0; i < classroomSize; i++)
    {
        flag = 0;
        classIndex = i;
        for (int j = 0; j < teacherSize; j++)
        {
            if (strcmp(classrooms[classIndex].teacherId,teachers[j].id)==0)
            {
                teacherIndex = j;
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            printf("|%-11s|%-21s|%-35s|%-21d|\n",classrooms[i].id, classrooms[i].name, teachers[teacherIndex].name, classrooms[i].studentCount);
            printf("|-----------|---------------------|-----------------------------------|---------------------|\n");
        }
        else{
            printf("|%-11s|%-21s|%-35s|%-21d|\n",classrooms[i].id, classrooms[i].name,"No teacher in charge", classrooms[i].studentCount);
            printf("|-----------|---------------------|-----------------------------------|---------------------|\n");
        }
    }
    backMenu();
}

void addClassroom(Classroom classrooms[], int *size, FILE *file)
{
    if (*size >= 100)
    {
        printf("The classroom list is full!\n");
        return;
    }
    Classroom newClassroom;
    while (1)
    {
        printf("Enter ID: ");
        getchar();
        fgets(newClassroom.id,sizeof(newClassroom.id),stdin);
        newClassroom.id[strcspn(newClassroom.id, "\n")] = '\0';
        int flag = 0;
        for (int i = 0; i < *size; i++)
        {
            if (strcmp(newClassroom.id,classrooms[i].id)==0)
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
    strcpy(classrooms[*size].id,newClassroom.id);
    printf("Enter name: ");
    fgets(newClassroom.name, sizeof(newClassroom.name), stdin);
    newClassroom.name[strcspn(newClassroom.name, "\n")] = '\0';
    strcpy(classrooms[*size].name,newClassroom.name);
    (*size)++;
    saveClassroom(classrooms, *size, file);
    printf("Add classroom success!\n");
    backMenu();
}

void editClassroom(Classroom classrooms[], int size, FILE *file)
{
    Classroom updateClassroom;
    char searchID[100];
    printf("Enter Classromm ID: ");
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
        strcpy(temp,classrooms[i].id);
        for (int i = 0; i < strlen(temp); i++)
        {
            temp[i] = toupper(temp[i]);
        }
        if (strcmp(temp,searchID)==0)
        {
            printf("===== Edit A Classroom =====\n");
            printf("Enter new name: ");
            fgets(classrooms[i].name, sizeof(classrooms[i].name), stdin);
            classrooms[i].name[strcspn(classrooms[i].name, "\n")] = '\0';
            saveClassroom(classrooms, size, file);
            printf("Edit classroom success!\n");
            saveClassroom(classrooms,size,file);
            backMenu();
            return;
        }
    }
    printf("No classroom found!\n");
    backMenu();
}

void deleteClassroom(Classroom classrooms[], int *size, FILE *file)
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
        strcpy(temp,classrooms[i].id);
        for (int i = 0; i < strlen(temp); i++)
        {
            temp[i] = toupper(temp[i]);
        }
        if (strcmp(temp,searchID)==0)
        {
            char x;
            printf("===== Delete A Classroom =====\n");
            printf("Are you sure want to delete this classroom?(Y/N) : ");
            scanf("%c",&x);
            x = toupper(x);
            switch (x)
            {
            case 'Y':
                for (int j = i; j < *size - 1; j++)
                {
                    classrooms[j] = classrooms[j + 1];
                }
                (*size)--;
                saveClassroom(classrooms, *size, file);
                printf("Classroom delete success!\n");
                backMenu();
                break;
            case 'N':
                printf("Classroom delete failed !\n");
                backMenu();
                break;
            default:
                printf("Invalid choice!\n");
                backMenu();
                break;
            }
        }
    }
    printf("No classroom found!\n");
}

void classroomDetail(Classroom classrooms[],Student students[],Teacher teachers[], int classroomSize,int studentSize,int teacherSize,FILE *file)
{
    char searchID[100];
    char studentSearchId[100];
    int classIndex;
    int studentIndex;
    int flag;
    printf("Enter ID: ");
    getchar();
    fgets(searchID,100,stdin);
    searchID[strcspn(searchID, "\n")] = '\0';
    for (int i = 0; i < strlen(searchID); i++)
    {
        searchID[i] = toupper(searchID[i]);
    }
    flag = 0;
    for (int i = 0; i < classroomSize; i++)
    {
        char temp[100];
        strcpy(temp,classrooms[i].id);
        for (int i = 0; i < strlen(temp); i++)
        {
            temp[i] = toupper(temp[i]);
        }
        if (strcmp(temp,searchID) == 0)
        {
            classIndex = i;
            flag = 1;
            int choice;
            printf("\nClassroom Information : \n");
            printf("ID : %s\n",classrooms[i].id);
            printf("Name : %s\n",classrooms[i].name);
            for (int i = 0; i < teacherSize; i++)
            {
                if (strcmp(classrooms[classIndex].teacherId,teachers[i].id)==0)
                {
                    printf("Teacher Name : %s\n",teachers[i].name);
                    break;
                }
            }
            printf("Currently Students : %d\n",classrooms[i].studentCount);
            printf("===== Menu =====\n");
            printf("[1]. Add A Student.\n");
            printf("[2]. Delete A Student.\n");
            printf("[3]. Exit.\n");
            printf("Enter the choice : ");
            scanf("%d",&choice);
            switch (choice)
            {
            case 1:
                printf("Enter ID: ");
                getchar();
                fgets(studentSearchId,100,stdin);
                studentSearchId[strcspn(studentSearchId, "\n")] = '\0';
                for (int i = 0; i < strlen(studentSearchId); i++)
                {
                    studentSearchId[i] = toupper(studentSearchId[i]);
                }
                flag = 0;
                for (int i = 0; i < studentSize; i++)
                {
                    if (strcmp(studentSearchId,students[i].id)==0)
                    {
                        studentIndex = i;
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    printf("No student found!\n");
                    return;
                }
                if (students[studentIndex].status == 1) 
                {
                printf("Student is already in another class!\n");
                return;
                }
                classrooms[classIndex].students[classrooms[classIndex].studentCount] = students[studentIndex];
                classrooms[classIndex].studentCount++;
                students[studentIndex].status = 1;
                saveClassroom(classrooms,classroomSize,file);
                printf("Add student to classroom successfully!\n");
                break;
            case 2:
                printf("Enter Student ID: ");
                getchar();
                fgets(studentSearchId,100,stdin);
                studentSearchId[strcspn(studentSearchId, "\n")] = '\0';
                for (int i = 0; i < strlen(studentSearchId); i++)
                {
                    studentSearchId[i] = toupper(studentSearchId[i]);
                }
                flag = 0;
                for (int i = 0; i < studentSize; i++)
                {
                    if (strcmp(studentSearchId,students[i].id)==0)
                    {
                        studentIndex = i;
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0)
                {
                    printf("No student found!\n");
                    return;
                }
                printf("Are you sure want to delete this student?(Y/N) : ");
                scanf("%d",&choice);
                choice = toupper(choice);
                switch (choice)
                {
                case 'Y':
                    students[studentIndex].status = 0;
                    for (int j = studentIndex; j < classrooms[classIndex].studentCount - 1; j++)
                    {
                        classrooms[classIndex].students[j] = classrooms[classIndex].students[j + 1];
                    }
                    classrooms[classIndex].studentCount--;
                    saveClassroom(classrooms,classroomSize,file);
                    printf("Student delete success!\n");
                    break;
                case 'N':
                    printf("Student delete failed !\n");
                    break;
                default:
                    printf("Invalid choice!\n");
                    break;
                }
                break;
            case 3:
                break;
            default:
                break;
            }
        }
    }
    if (flag == 0)
    {
        printf("No classroom found!\n");
    }
}

void addStudentToClass(Classroom classrooms[], int classroomSize, Student students[], int studentSize,FILE *file)
{
    char searchClassId[100];
    char searchStudentId[100];
    int classIndex;
    int studentIndex;
    int flag;
    printf("Enter Classroom ID: ");
    getchar();
    fgets(searchClassId, sizeof(searchClassId), stdin);
    searchClassId[strcspn(searchClassId, "\n")] = '\0';
    for (int i = 0; i < strlen(searchClassId); i++) {
        searchClassId[i] = toupper(searchClassId[i]);
    }
    flag = 0;
    for (int i = 0; i < classroomSize; i++) {
        if (strcmp(searchClassId, classrooms[i].id) == 0) {
            classIndex = i;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("Classroom not found!\n");
        return;
    }
    
    if (classrooms[classIndex].studentCount >= 30) {
        printf("The classroom is full!\n");
        return;
    }
    printf("Enter Student ID: ");
    fgets(searchStudentId, sizeof(searchStudentId), stdin);
    searchStudentId[strcspn(searchStudentId, "\n")] = '\0';
    for (int i = 0; i < strlen(searchStudentId); i++) {
        searchStudentId[i] = toupper(searchStudentId[i]);
    }
    flag = 0;
    for (int i = 0; i < studentSize; i++) {
        if (strcmp(searchStudentId, students[i].id) == 0) {
            studentIndex = i;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("Student not found!\n");
        return;
    }
    if (students[studentIndex].status == 1) {
        printf("Student is already in another class!\n");
        return;
    }
    classrooms[classIndex].students[classrooms[classIndex].studentCount] = students[studentIndex];
    classrooms[classIndex].studentCount++;
    students[studentIndex].status = 1;
    saveClassroom(classrooms,classroomSize,file);
    printf("Add student to classroom successfully!\n");
}

void deleteStudentFromClass(Classroom classrooms[],Student students[], int classroomSize,int studentSize, FILE *file)
{
    char searchClassroomId[100];
    char searchStudentId[100];
    int classIndex;
    int studentIndex;
    int flag;
    char choice;
    printf("Enter Classroom ID: ");
    getchar();
    fgets(searchClassroomId,100,stdin);
    searchClassroomId[strcspn(searchClassroomId, "\n")] = '\0';
    for (int i = 0; i < strlen(searchClassroomId); i++)
    {
        searchClassroomId[i] = toupper(searchClassroomId[i]);
    }
    flag = 0;
    for (int i = 0; i < classroomSize; i++)
    {
        char temp[100];
        strcpy(temp,classrooms[i].id);
        for (int i = 0; i < strlen(temp); i++)
        {
            temp[i] = toupper(temp[i]);
        }
        if (strcmp(temp,searchClassroomId)==0)
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
    printf("Enter Student ID: ");
    fgets(searchStudentId,100,stdin);
    searchStudentId[strcspn(searchStudentId, "\n")] = '\0';
    for (int i = 0; i < strlen(searchStudentId); i++)
    {
        searchStudentId[i] = toupper(searchStudentId[i]);
    }
    flag = 0;
    for (int i = 0; i < studentSize; i++)
    {
        if (strcmp(searchStudentId,students[i].id)==0)
        {
            studentIndex = i;
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        printf("No student found!\n");
        return;
    }
    printf("Are you sure want to delete this student?(Y/N) : ");
    scanf("%c",&choice);
    choice = toupper(choice);
    switch (choice)
    {
    case 'Y':
        students[studentIndex].status = 0;
        for (int j = studentIndex; j < classrooms[classIndex].studentCount - 1; j++)
        {
            classrooms[classIndex].students[j] = classrooms[classIndex].students[j + 1];
        }
        classrooms[classIndex].studentCount--;
        saveClassroom(classrooms,classroomSize,file);
        printf("Student delete success!\n");
        break;
    case 'N':
        printf("Student delete failed !\n");
        break;
    default:
        printf("Invalid choice!\n");
        break;
    }
}

void sortClassroom(Classroom classrooms[],int classroomSize){
    int choice;
    printf("[1]. Sort ascending by name.\n");
    printf("[2]. Sort descending by name.\n");
    printf("[3]. Exit.\n");
    printf("Enter the choice : ");
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        for (int i = 0; i < classroomSize; i++)
        {
            for (int j = 0; j < classroomSize-1-i; j++)
            {
                if (strcmp(classrooms[i].name,classrooms[j].name)>0)
                {
                    Classroom temp = classrooms[j];
                    classrooms[j] = classrooms[j+1];
                    classrooms[j] = temp;
                }
            }
        }
        printf("Classroom sort success!\n");
        backMenu();
        break;
    case 2:
        for (int i = 0; i < classroomSize; i++)
        {
            for (int j = 0; j < classroomSize-1-i; j++)
            {
                if (strcmp(classrooms[i].name,classrooms[j].name)<0)
                {
                    Classroom temp = classrooms[j];
                    classrooms[j] = classrooms[j+1];
                    classrooms[j] = temp;
                }
            }
        }
        printf("Classroom sort success!\n");
        backMenu();
        break;
    case 3:
        break;
    default:
        printf("Invalid choice!\n");
        break;
    }
}