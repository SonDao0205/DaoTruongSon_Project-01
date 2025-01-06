#include "include/datatype.h"
#include "include/studentsManagement.h"
#include "include/adminAccounts.h"
#include "include/secondaryFeatures.h"
#include "include/teacherManagement.h"
#include "include/classroomManagement.h"
#include "include/studentAccounts.h"
#include "include/teacherAccounts.h"
#include "src/studentsManagement.c"
#include "src/secondaryFeatures.c"
#include "src/adminAccounts.c"
#include "src/studentAccounts.c"
#include "src/teacherAccounts.c"
#include "src/teacherManagement.c"
#include "src/classroomManagement.c"


int main()
{
    adminAccount adminAccounts[100];
    studentAccount studentAccounts[100];
    teacherAccount teacherAccounts[100];
    FILE *file;
    int adminAccountSize = 0;
    int studentAccountSize = 0;
    int teacherAccountSize = 0;
    int loginSuccess;
    int choice;
    adminLoadAccounts(adminAccounts, &adminAccountSize);
    studentLoadAccounts(studentAccounts, &studentAccountSize);
    teacherLoadAccounts(teacherAccounts, &teacherAccountSize);
    Student students[100];
    Teacher teachers[100];
    Classroom classrooms[100];
    int studentsSize = 0;
    int teacherSize = 0;
    int classroomSize = 0;
    loadStudents(students, &studentsSize, file);
    loadTeachers(teachers,&teacherSize,file);
    loadClassroom(classrooms,&classroomSize,file);
    do
    {
        printf("\n======== CHOOSE YOUR ROLE ========\n");
        printf("           [1]. Admin.\n");
        printf("           [2]. Student.\n");
        printf("           [3]. Teacher.\n");
        printf("           [4]. Exit\n");
        printf("==================================\n");
        printf("          Enter The Choice : ");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            loginSuccess = 0;
            do
            {
                printf("\n======== MENU ========\n");
                printf("    [1]. Log In\n");
                printf("    [2]. Exit\n");
                printf("========================\n");
                printf("   Enter The Choice : ");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    if (adminLogin(adminAccounts, adminAccountSize))
                    {
                        loginSuccess = 1;
                        printf("Log in successful!\n");
                    }
                    else
                    {
                        printf("Wrong username or password!\n");
                    }
                    break;
                case 2:
                    goodBye();
                    break;
                default:
                    printf("Invalid choice!\n");
                    break;
                }
            } while (loginSuccess == 0 && choice != 3);
            if (loginSuccess)
            {
                do
                {
                    printf("\n============= MENU =============\n");
                    printf("      [1]. Student Management\n");
                    printf("      [2]. Teacher Management\n");
                    printf("      [3]. Classroom Management\n");
                    printf("      [4]. Exit\n");
                    printf("==================================\n");
                    printf("       Enter The Choice : ");
                    scanf("%d",&choice);
                    switch (choice)
                    {
                    case 1:
                        loadStudents(students, &studentsSize, file);
                        do
                        {
                            printf("\n========== Student Management ==========\n");
                            printf("       [1]. Show All Students.\n");
                            printf("       [2]. Add A New Students.\n");
                            printf("       [3]. Edit A Students.\n");
                            printf("       [4]. Delete A Students.\n");
                            printf("       [5]. Search A Students.\n");
                            printf("       [6]. Sort Students.\n");
                            printf("       [7]. Exit.\n");
                            printf("=========================================\n");
                            printf("       Enter The Choice : ");
                            scanf("%d", &choice);
                            switch (choice)
                            {
                            case 1:
                                displayStudents(students, studentsSize);
                                break;
                            case 2:
                                printf("===== Add A New Students =====\n");
                                addStudent(students, &studentsSize, file);
                                break;
                            case 3:
                                printf("===== Edit A Students =====\n");
                                editStudent(students, studentsSize, file);
                                break;
                            case 4:
                                printf("===== Delete A Students =====\n");
                                deleteStudent(students, &studentsSize, file);
                                break;
                            case 5:
                                printf("===== Search A Students =====\n");
                                searchStudent(students, studentsSize);
                                break;
                            case 6:
                                printf("===== Sort Students =====\n");
                                sortStudents(students, studentsSize);
                                saveStudents(students, studentsSize, file);
                                break;
                            case 7:
                                goodBye();
                                break;
                            default:
                                printf("Invalid choice!\n");
                            }
                        } while (choice != 7);
                        break;
                    case 2:
                        do
                        {
                            loadTeachers(teachers,&teacherSize,file);
                            loadClassroom(classrooms,&classroomSize,file);
                            printf("\n========== Teacher Management ==========\n");
                            printf("       [1]. Show All Teachers.\n");
                            printf("       [2]. Add A New Teachers.\n");
                            printf("       [3]. Edit A Teachers.\n");
                            printf("       [4]. Delete A Teachers.\n");
                            printf("       [5]. Search A Teachers.\n");
                            printf("       [6]. Add A Classroom For Teacher.\n");
                            printf("       [7]. Exit.\n");
                            printf("=========================================\n");
                            printf("       Enter The Choice : ");
                            scanf("%d", &choice);
                            switch (choice)
                            {
                            case 1:
                                displayTeachers(teachers, teacherSize);
                                break;
                            case 2:
                                printf("===== Add A New Teacher =====\n");
                                addTeacher(teachers, &teacherSize, file);
                                break;
                            case 3:
                                printf("===== Edit A Teacher =====\n");
                                editTeacher(teachers, teacherSize, file);
                                break;
                            case 4:
                                printf("===== Delete A Teacher =====\n");
                                deleteTeacher(teachers, &teacherSize, file);
                                break;
                            case 5:
                                printf("===== Search A Teacher =====\n");
                                searchTeacher(teachers, teacherSize);
                                break;
                            case 6:
                                printf("===== Add A Classroom For Teacher =====\n");
                                AddClassroomForTeacher(classrooms,teachers,classroomSize,teacherSize);
                                saveClassroom(classrooms,classroomSize,file);
                                break;
                            case 7:
                                goodBye();
                                break;
                            default:
                                printf("Invalid choice!\n");
                                break;
                            }
                        } while (choice != 7);
                        break;
                    case 3:
                        do
                        {
                            loadTeachers(teachers,&teacherSize,file);
                            loadClassroom(classrooms,&classroomSize,file);
                            loadStudents(students, &studentsSize, file);
                            printf("\n========== Classroom Management ==========\n");
                            printf("       [1]. Show All Classrooms.\n");
                            printf("       [2]. Add A New Classroom.\n");
                            printf("       [3]. Edit A Classroom.\n");
                            printf("       [4]. Delete A Classroom.\n");
                            printf("       [5]. Classroom Details.\n");
                            printf("       [6]. Add A Student To Classroom.\n");
                            printf("       [7]. Delete A Student From Classroom.\n");
                            printf("       [8]. Sort Classroom.\n");
                            printf("       [9]. Exit.\n");
                            printf("=========================================\n");
                            printf("       Enter The Choice : ");
                            scanf("%d", &choice);
                            switch (choice)
                            {
                            case 1:
                                displayClassroom(classrooms,teachers,classroomSize,teacherSize);
                                break;
                            case 2:
                                printf("===== Add A New Classroom =====\n");
                                addClassroom(classrooms,&classroomSize,file);
                                break;
                            case 3:
                                printf("===== Edit A Classroom =====\n");
                                editClassroom(classrooms,classroomSize,file);
                                break;
                            case 4:
                                printf("===== Delete A Classroom =====\n");
                                deleteClassroom(classrooms,&classroomSize,file);
                                break;
                            case 5:
                                printf("===== Classroom Detail =====\n");
                                classroomDetail(classrooms,students,teachers,classroomSize,studentsSize,teacherSize,file);
                                break;
                            case 6:
                                printf("===== Add A Student To Classroom =====\n");
                                addStudentToClass(classrooms,classroomSize,students,studentsSize,file);
                                break;
                            case 7:
                                printf("===== Delete A Student From Classroom =====\n");
                                deleteStudentFromClass(classrooms,students,classroomSize,studentsSize,file);
                                break;
                            case 8:
                                printf("===== Sort Classroom =====\n");
                                sortClassroom(classrooms,classroomSize);
                                break;
                            case 9:
                                break;
                            default:
                                printf("Invalid choice!\n");
                                break;
                            }
                        } while (choice != 9);
                        break;
                    case 4:
                        goodBye();
                        break;
                    default:
                        printf("Invalid choice!\n");
                        break;
                    }
                } while (choice != 4);
            }
                break;
        case 2:
            loginSuccess = 0;
            do
            {
                printf("\n======== MENU ========\n");
                printf("    [1]. Log In\n");
                printf("    [2]. Sign Up\n");
                printf("    [3]. Exit\n");
                printf("========================\n");
                printf("   Enter The Choice : ");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    if (studentLogin(studentAccounts, studentAccountSize))
                    {
                        loginSuccess = 1;
                        printf("Log in successful!\n");
                    }
                    else
                    {
                        printf("Wrong username or password!\n");
                    }
                    break;
                case 2:
                    studentRegisterAccount(studentAccounts, &studentAccountSize);
                    break;
                case 3:
                    goodBye();
                    break;
                default:
                    printf("Invalid choice!\n");
                    break;
                }
            } while (loginSuccess == 0 && choice != 3);
            if (loginSuccess)
            {
                loadStudents(students, &studentsSize, file);
                do
                {
                    printf("============== Menu ==============\n");
                    printf("      [1]. Show All Students.\n");
                    printf("      [2]. Exit.\n");
                    printf("==================================\n");
                    printf("      Enter The Choice : ");
                    scanf("%d",&choice);
                    switch (choice)
                    {
                    case 1:
                        displayStudents(students, studentsSize);
                        break;
                    case 2:
                        goodBye();
                        break;
                    default:
                        printf("Invalid choice!\n");
                        break;
                    }
                } while (choice !=2);
            }
            break;
        case 3:
            loginSuccess = 0;
            do
            {
                
                printf("\n======== MENU ========\n");
                printf("    [1]. Log In\n");
                printf("    [2]. Sign Up\n");
                printf("    [3]. Exit\n");
                printf("========================\n");
                printf("   Enter The Choice : ");
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    if (teacherLogin(teacherAccounts, teacherAccountSize))
                    {
                        loginSuccess = 1;
                        printf("Log in successful!\n");
                    }
                    else
                    {
                        printf("Wrong username or password!\n");
                    }
                    break;
                case 2:
                    teacherRegisterAccount(teacherAccounts, &teacherAccountSize);
                    break;
                case 3:
                    goodBye();
                    break;
                default:
                    printf("Invalid choice!\n");
                    break;
                }
            } while (loginSuccess == 0 && choice != 3);
            if (loginSuccess)
            {
                do
                {
                    loadStudents(students, &studentsSize, file);
                    printf("\n========== Student Management ==========\n");
                    printf("       [1]. Show All Students.\n");
                    printf("       [2]. Add A New Students.\n");
                    printf("       [3]. Edit A Students.\n");
                    printf("       [4]. Delete A Students.\n");
                    printf("       [5]. Search A Students.\n");
                    printf("       [6]. Sort Students.\n");
                    printf("       [7]. Exit.\n");
                    printf("=========================================\n");
                    printf("       Enter The Choice : ");
                    scanf("%d", &choice);
                    switch (choice)
                    {
                    case 1:
                        displayStudents(students, studentsSize);
                        break;
                    case 2:
                        printf("===== Add A New Students =====\n");
                        addStudent(students, &studentsSize, file);
                        break;
                    case 3:
                        printf("===== Edit A Students =====\n");
                        editStudent(students, studentsSize, file);
                        break;
                    case 4:
                        printf("===== Delete A Students =====\n");
                        deleteStudent(students, &studentsSize, file);
                        break;
                    case 5:
                        printf("===== Search A Students =====\n");
                        searchStudent(students, studentsSize);
                        break;
                    case 6:
                        printf("===== Sort Students =====\n");
                        sortStudents(students, studentsSize);
                        saveStudents(students, studentsSize, file);
                        break;
                    case 7:
                        goodBye();
                        break;
                    default:
                        printf("Invalid choice!\n");
                    }
                } while (choice != 7);
            }
            break;
        case 4:
            goodBye();
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    } while (choice != 4);
}