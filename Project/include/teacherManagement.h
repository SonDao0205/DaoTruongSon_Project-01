#include"datatype.h"
#include "secondaryFeatures.h"

void loadTeachers(Teacher teachers[], int *size, FILE *file);
void saveTeachers(Teacher teachers[], int size, FILE *file);
void displayTeachers(Teacher teachers[], int size);
void addTeacher(Teacher teachers[], int *size, FILE *file);
void editTeacher(Teacher teachers[], int size, FILE *file);
void deleteTeacher(Teacher teachers[], int *size, FILE *file);
void searchTeacher(Teacher teachers[], int size);
void sortTeachers(Teacher teachers[], int size);
void AddClassroomForTeacher(Classroom classrooms[],Teacher teachers[],int classroomSize,int teacherSize);
