#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    char name[100];
    char subject[50];
    char class_name[50];
    float grade;
    float gpa;
};

// Function prototypes
void add_student(struct Student **students, int *count, int *capacity);
void view_students(struct Student *students, int count);
void save_students(struct Student *students, int count);
void load_students(struct Student **students, int *count, int *capacity);
float calculate_average(struct Student *students, int count);

int main()
{
    struct Student *students = NULL;
    int count = 0;
    int capacity = 2;
    int choice = 0;

    // Allocate memory
    students = malloc(capacity * sizeof(struct Student));
    if (students == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    do {
        printf("\n==== STUDENT GRADE MANAGER ====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Calculate Average\n");
        printf("4. Save to File\n");
        printf("5. Load from File\n");
        printf("6. Exit\n");
        printf("===============================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline

        switch(choice)
        {
            case 1:
                add_student(&students, &count, &capacity);
                break;
            case 2:
                view_students(students, count);
                break;
            case 3:
                printf("Average grade: %.2f\n", calculate_average(students, count));
                break;
            case 4:
                save_students(students, count);
                break;
            case 5:
                load_students(&students, &count, &capacity);
                break;
            case 6:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 6);

    free(students);
    return 0;
}
// Functions
void add_student(struct Student **students, int *count, int *capacity)
{
    char name[100] = "";
    char class_name[50] = "";
    char subject[50] = "";
    float grade = 0.0f;
    float gpa = 0.0f;

    printf("Enter the students name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Enter class name: ");
    fgets(class_name, sizeof(class_name), stdin);
    class_name[strcspn(class_name, "\n")] = '\0';

    printf("Enter the subject name: ");
    fgets(subject, sizeof(subject), stdin);
    subject[strcspn(subject, "\n")] = '\0';

    printf("Enter the grade: ");
    scanf("%f", &grade);
    getchar();

    gpa = grade / 25;

    strcpy((*students)[*count].name, name);
    strcpy((*students)[*count].subject, subject);
    strcpy((*students)[*count].class_name, class_name);
    (*students)[*count].grade = grade;
    (*students)[*count].gpa = gpa;

    (*count)++;
    printf("✅ Student added!\n");
}
