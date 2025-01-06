#include"datatype.h"
#include "secondaryFeatures.h"

void loadClassroom(Classroom classrooms[], int *size, FILE *file);
void saveClassroom(Classroom classrooms[], int size, FILE *file);
void displayClassroom(Classroom classrooms[],Teacher teachers[], int classroomSize,int teacherSize);
void displayInformationClassroom(Classroom classrooms[],int size,char searchID[100]);
void addClassroom(Classroom classrooms[], int *size, FILE *file);
void editClassroom(Classroom classrooms[], int size, FILE *file);
void deleteClassroom(Classroom classrooms[], int *size, FILE *file);
void classroomDetail(Classroom classrooms[],Student students[],Teacher teachers[], int classroomSize,int studentSize,int teacherSize,FILE *file);
void sortClassroom(Classroom classrooms[], int size);
void addStudentToClass(Classroom classrooms[], int classroomSize, Student students[], int studentSize,FILE *file);
void deleteStudentFromClass(Classroom classrooms[],Student students[], int classroomSize,int studentSize, FILE *file);
void sortClassroom(Classroom classrooms[],int classroomSize);