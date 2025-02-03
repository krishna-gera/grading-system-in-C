#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_NAME_LENGTH 50

// Structure to store student data
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    double grades[5];
    double average;
    char letterGrade;
} Student;

// Function prototypes
void addStudent(Student students[], int *count);
void deleteStudent(Student students[], int *count);
void updateStudent(Student students[], int count);
void viewStudents(Student students[], int count);
void calculateAverageAndGrade(Student *student);

int main() {
    int choice;
    Student students[MAX_STUDENTS];
    int studentCount = 0;

    while (1) {
        printf("\nStudent Grade Management System:\n");
        printf("1. Add Student\n");
        printf("2. Delete Student\n");
        printf("3. Update Student\n");
        printf("4. View Students\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent(students, &studentCount);
                break;
            case 2:
                deleteStudent(students, &studentCount);
                break;
            case 3:
                updateStudent(students, studentCount);
                break;
            case 4:
                viewStudents(students, studentCount);
                break;
            case 5:
                exit(0);
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

// Function to add a new student
void addStudent(Student students[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Error! Maximum student limit reached.\n");
        return;
    }

    Student newStudent;
    newStudent.id = *count + 1;
    printf("Enter student name: ");
    getchar(); // Clear the newline character left by scanf
    fgets(newStudent.name, MAX_NAME_LENGTH, stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = '\0'; // Remove newline character

    printf("Enter grades for 5 subjects:\n");
    for (int i = 0; i < 5; i++) {
        printf("Subject %d: ", i + 1);
        scanf("%lf", &newStudent.grades[i]);
    }

    calculateAverageAndGrade(&newStudent);
    students[*count] = newStudent;
    (*count)++;
    printf("Student added successfully!\n");
}

// Function to delete a student
void deleteStudent(Student students[], int *count) {
    int id;
    printf("Enter student ID to delete: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            found = 1;
            for (int j = i; j < *count - 1; j++) {
                students[j] = students[j + 1];
            }
            (*count)--;
            printf("Student deleted successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Error! Student not found.\n");
    }
}

// Function to update student information
void updateStudent(Student students[], int count) {
    int id;
    printf("Enter student ID to update: ");
    scanf("%d", &id);

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) {
            found = 1;
            printf("Enter new name: ");
            getchar(); // Clear the newline character left by scanf
            fgets(students[i].name, MAX_NAME_LENGTH, stdin);
            students[i].name[strcspn(students[i].name, "\n")] = '\0'; // Remove newline character

            printf("Enter new grades for 5 subjects:\n");
            for (int j = 0; j < 5; j++) {
                printf("Subject %d: ", j + 1);
                scanf("%lf", &students[i].grades[j]);
            }

            calculateAverageAndGrade(&students[i]);
            printf("Student updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Error! Student not found.\n");
    }
}

// Function to view all students
void viewStudents(Student students[], int count) {
    if (count == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\n%-5s %-20s %-10s %-10s %-10s %-10s %-10s %-10s %-10s\n", "ID", "Name", "Subject 1", "Subject 2", "Subject 3", "Subject 4", "Subject 5", "Average", "Grade");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %-10.2lf %-10.2lf %-10.2lf %-10.2lf %-10.2lf %-10.2lf %-10c\n",
               students[i].id, students[i].name, students[i].grades[0], students[i].grades[1], students[i].grades[2], students[i].grades[3], students[i].grades[4], students[i].average, students[i].letterGrade);
    }
}

// Function to calculate average grade and letter grade for a student
void calculateAverageAndGrade(Student *student) {
    double sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += student->grades[i];
    }
    student->average = sum / 5;

    if (student->average >= 90) {
        student->letterGrade = 'A';
    } else if (student->average >= 80) {
        student->letterGrade = 'B';
    } else if (student->average >= 70) {
        student->letterGrade = 'C';
    } else if (student->average >= 60) {
        student->letterGrade = 'D';
    } else {
        student->letterGrade = 'E';
    }
}
