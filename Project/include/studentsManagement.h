#include"datatype.h"
#include "secondaryFeatures.h"

void loadStudents(Student students[], int *size, FILE *file);
void saveStudents(Student students[], int size, FILE *file);
void displayStudents(Student students[], int size);
void displayInformationStudents(Student students[],int size,char searchID[100]);
void addStudent(Student students[], int *size, FILE *file);
void editStudent(Student students[], int size, FILE *file);
void deleteStudent(Student students[], int *size, FILE *file);
void searchStudent(Student students[], int size);
void sortStudents(Student students[], int size);



