#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Student
{
    int id;
    char name[100];
    char subject[50];
    char class_name[50];
    float grade;
    float gpa;
 
};
struct Admin
{
    char admin_username[64];
    char admin_password[64];
};

// Function prototypes
void add_student(struct Student **students, int *count, int *capacity);
void view_students(struct Student *students, int count);
void save_students(struct Student *students, int count);
void load_students(struct Student **students, int *count, int *capacity);
float calculate_average(struct Student *students, int count);
int admin_login(struct Admin *admin);
void student_login(struct Student *students, int count);
int generate_student_id();

int main()
{
    struct Admin admin = {"admin", "admin123"};
    struct Student *students = NULL;
    int count = 0;
    int capacity = 2;
    int welcome_choice = 0;
    int admin_choice = 0;

    srand(time(NULL)); // make the random number for student's ID
    // Allocate memory
    students = malloc(capacity * sizeof(struct Student));
    if (students == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    do
   {
       printf("\n===== WELCOME =====\n");
       printf("1. Admin Login\n");
       printf("2. Student Login\n");
       printf("3. Exit\n");
       printf("====================\n");
       printf("Enter: ");
       scanf("%d", &welcome_choice);
       getchar();

       switch(welcome_choice)
       {
           case 1:
               if(admin_login(&admin))
               {
                   do
                   {
                       printf("\n====ADMIN MNEU====\n");
                       printf("1. Add Student\n");
                       printf("2. View Students\n");
                       printf("3. Calculate Average\n");
                       printf("4. Save to File\n");
                       printf("5. Load from File\n");
                       printf("6. Exit\n");
                       printf("===============================\n");
                       printf("Enter your choice: ");
                       scanf("%d", &admin_choice);
                       getchar();

                       switch(admin_choice)
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
                   }while(admin_choice != 6);
               }
               break;
           case 2:
               student_login(students, count);
               break;
            case 3:
               printf("Goodbye!\n");
               break;
            default:
               printf("Invalid choice\n");
               break;
       }
   }while(welcome_choice != 3);

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

    if (*count == *capacity)
    {
        *capacity *= 2;
        struct Student *temp = realloc(*students, *capacity * sizeof(struct Student));
        if (temp == NULL)
        {
            printf("Memory allocation failed!\n");
            return;
        }
        *students = temp;
    }

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
    (*students)[*count].id = generate_student_id();

    printf("Student ID: %d\n", (*students)[*count].id);

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
        fprintf(file, "%d|%s|%s|%s|%.2f|%.2f\n",
        students[i].id,
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
        if(token == NULL) continue;
        (*students)[*count].id = atoi(token);

        token = strtok(NULL, "|");
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
int admin_login(struct Admin *admin)
{
    char admin_username[64] = "";
    char admin_password[64] = "";
    
    printf("Enter the admin's username: ");
    fgets(admin_username, sizeof(admin_username), stdin);
    admin_username[strcspn(admin_username, "\n")] = '\0';
    
    printf("Enter the admin's password: ");
    fgets(admin_password, sizeof(admin_password), stdin);
    admin_password[strcspn(admin_password, "\n")] = '\0';
    
    if (strcmp(admin_username, admin->admin_username) == 0 && 
        strcmp(admin_password, admin->admin_password) == 0)
    {
        printf("✅ Hello dear admin!\n");
        return 1;
    }
    else
    {
        printf("❌ Wrong password or username!\n");
        return 0;
    }
}

void student_login(struct Student *students, int count)
{
    int entered_id = 0;
    int found = 0;

    printf("Enter your ID: ");
    scanf("%d", &entered_id);
    getchar();

    for(int i = 0; i < count; i++)
    {
        if(students[i].id == entered_id)
        {
            printf("Name: %s\n", students[i].name);
            printf("Class: %s\n", students[i].class_name);
            printf("Subject: %s\n", students[i].subject);
            printf("Grade: %.2f\n", students[i].grade);
            printf("GPA: %.2f\n", students[i].gpa);

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("Student Not found!!\n");
    }
}

int generate_student_id()
{
    return rand() % 90000 + 10000;
}
