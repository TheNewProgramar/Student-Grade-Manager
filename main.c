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
                break;
        }
    } while(choice != 6);

    free(students);
    return 0;
}
// Functions
void add_student(struct Student **students, int *count, int *capacity) //add students 
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

 void view_students(struct Student *students, int count) // view students
{
    if(count == 0)
    {
        printf("there is no Student add yet");
        return;
    }

    printf("===ALL STUDENTS===\n");
    for(int i = 0; i < count; i++)
    { 
        printf("Name: %s\n", students[i].name);
        printf("class name: %s\n", students[i].class_name);
        printf("subject: %s\n", students[i].subject);
        printf("grade: %.2f\n", students[i].grade);
        printf("gpa: %.2f\n", students[i].gpa);
        printf("--------------------------------------\n");
    }
}

float calculate_average(struct Student *students, int count) // calculate average
{
    float total = 0.0f;

    if(count == 0)
    {
        printf("There is problem with the grades cheack theme first");
        return 0;
    }
    
    for(int i = 0; i < count; i++)
    {
        total += students[i].grade;
    }
    return total / count;
}

void save_students(struct Student *students, int count)
{
    FILE *file = fopen("students.txt", "w");
    
    if(file == NULL)
    {
        printf("We have an Error for Opning the information file");
        return;
    }
    
    for(int i = 0; i < count; i++)
    {
        fprintf(file, "%s|%s|%s|%.2f|%.2f\n", 
        students[i].name,
        students[i].class_name,
        students[i].subject,
        students[i].grade,
        students[i].gpa);
    }

    fclose(file);
    printf("✅ %d students saved!\n", count);
}

void load_students(struct Student **students, int *count, int *capacity)
{
    FILE *file = fopen("students.txt", "r");
    
    if (file == NULL)
    {
        printf("There is no file saved yet");
        return; 
    }
    
    char line[512];
    
    while(fgets(line, sizeof(line), file) != NULL)
    {
        line[strcspn(line, "\n")] = '\0';
        
        if (*count == *capacity)
        {
            *capacity *= 2;
            struct Student *temp = realloc(*students, *capacity * sizeof(struct Student));
            if (temp == NULL) {
                printf("Memory allocation failed!\n");
                fclose(file);
                return;
            }
            *students = temp;
        }
        
        char *token = strtok(line, "|");
        if (token == NULL) continue;
        strcpy((*students)[*count].name, token);
        
        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strcpy((*students)[*count].class_name, token);

        token = strtok(NULL, "|");
        if (token == NULL) continue;
        strcpy((*students)[*count].subject, token);
        
        token = strtok(NULL, "|");
        if (token == NULL) continue;
        (*students)[*count].grade = atof(token);
        
        token = strtok(NULL, "|");
        if (token == NULL) continue;
        (*students)[*count].gpa = atof(token);
        
        (*count)++;
    }
    fclose(file);
    
    if (*count > 0) {
        printf("✅ %d students loaded!\n", *count);
    }
}
