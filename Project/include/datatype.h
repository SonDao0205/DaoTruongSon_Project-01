#pragma once
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

typedef struct
{
    char id[100];
    char name[100];
    char email[200];
    char phone[15];
    char password[100];
    int status;
}Student;

typedef struct
{
    char username[100];
    char password[100];
}adminAccount;

typedef struct
{
    char username[100];
    char password[100];
}studentAccount;

typedef struct
{
    char username[100];
    char password[100];
}teacherAccount;

typedef struct{
    char id[100];
    char name[100];
    char email[200];
    char phone[15];
    char password[100];
}Teacher;

typedef struct 
{
    char id[100];
    char teacherId[100];
    char name[100];
    Student students[100];
    int studentCount;
    int status;
}Classroom;
