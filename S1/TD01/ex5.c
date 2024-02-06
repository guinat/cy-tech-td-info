#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Compile : gcc ex5.c

#define NUM_MARK 10

typedef struct Student
{
    char first_name[50];
    char last_name[50];
    int group;
    int mark[NUM_MARK];
} student_t;

typedef struct Node
{
    student_t student;
    struct Node *next;
} node_t;

typedef struct List
{
    node_t *head;
} list_t;

double array_average(int arr[], int size)
{
    double sum = 0.0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return sum / size;
}

void input_student(list_t *lst)
{
    student_t student_new;
    printf("Enter student's first name: ");
    scanf("%s", student_new.first_name);
    printf("Enter student's last name: ");
    scanf("%s", student_new.last_name);
    printf("Enter student's group number: ");
    scanf("%d", &student_new.group);

    for (int i = 0; i < NUM_MARK; i++)
    {
        student_new.mark[i] = rand() % 21;
    }

    node_t *node_new = malloc(sizeof(node_t));
    if (!node_new)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node_new->student = student_new;
    node_new->next = NULL;

    if (lst->head == NULL)
        lst->head = node_new;
    else
    {
        node_t *current = lst->head;
        while (current->next != NULL)
            current = current->next;
        current->next = node_new;
    }
}

student_t *student_find(char *first_name, char *last_name, list_t *lst)
{
    node_t *current = lst->head;
    while (current != NULL)
    {
        if (strcmp(current->student.first_name, first_name) == 0 && strcmp(current->student.last_name, last_name) == 0)
            return &current->student;
        current = current->next;
    }
    return NULL;
}

void list_per_group(list_t *lst, int group)
{
    node_t *current = lst->head;
    while (current != NULL)
    {
        if (current->student.group == group)
            printf("%s %s\n", current->student.first_name, current->student.last_name);
        current = current->next;
    }
}

int main()
{
    srand(time(NULL));

    list_t student_list = {NULL};

    for (int i = 0; i < 3; i++)
    {
        input_student(&student_list);
    }

    char search_first_name[] = "Hello";
    char search_last_name[] = "World";
    student_t *student = student_find(search_first_name, search_last_name, &student_list);
    if (student)
    {
        double average = array_average(student->mark, NUM_MARK);
        printf("Average grade for %s %s is: %.2f\n", student->first_name, student->last_name, average);
    }
    else
    {
        printf("Student %s %s not found.\n", search_first_name, search_last_name);
    }

    node_t *current = student_list.head;
    double total_average = 0.0;
    int student_count = 0;
    while (current != NULL)
    {
        double average_ = array_average(current->student.mark, NUM_MARK);
        printf("Average grade for %s %s is: %.2f\n", current->student.first_name, current->student.last_name, average_);
        total_average += average_;
        student_count++;
        current = current->next;
    }
    double promotion_average = total_average / student_count;
    printf("Average grade for the entire promotion is: %.2f\n", promotion_average);

    current = student_list.head;
    student_t *lowest_average_student = &current->student;
    double lowest_average = array_average(current->student.mark, NUM_MARK);
    while (current != NULL)
    {
        double average__ = array_average(current->student.mark, NUM_MARK);
        if (average__ < lowest_average)
        {
            lowest_average = average__;
            lowest_average_student = &current->student;
        }
        current = current->next;
    }
    printf("Student with the lowest average grade: %s %s with an average of %.2f\n",
           lowest_average_student->first_name, lowest_average_student->last_name, lowest_average);

    current = student_list.head;
    while (current != NULL)
    {
        node_t *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
