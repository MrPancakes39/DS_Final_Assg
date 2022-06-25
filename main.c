/** @file main.c
 * The main file program
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define INPUT_SIZE 128 ///< Defines maximum buffer that can be used for input.

/**
 * Defines a Teacher object.
 */
typedef struct Teacher
{
    int id;     ///< the id of the Teacher.
    int age;    ///< the age of the Teacher.
    char *name; ///< the name of the Teacher.
} Teacher;

/**
 * Defines a list node in the Teacher LinkedList.
 */
typedef struct ListNode
{
    Teacher *t;                ///< represents a Teacher.
    struct ListNode *nextNode; ///< points to the next ListNode in the List.
} ListNode;

/**
 * Defines a LinkedList of Teacher objects.
 */
typedef struct List
{
    ListNode *head; ///< represents the start of the List.
    int length;     ///< stores the number of Teacher objects in the List.
} List;

// =======================================================================================
// ================================ Teacher Functions ====================================
// =======================================================================================

/**
 * Allocates and Creates a Teacher object.
 * @param[in] id the id of the Teacher.
 * @param[in] age the age of the Teacher.
 * @param[in] name the name of the Teacher.
 * @return a Teacher object.
 */
Teacher *createTeacher(int id, int age, char *name)
{
    Teacher *t = (Teacher *)malloc(sizeof(Teacher));
    t->id = id;
    t->age = age;
    int name_size = strlen(name) + 1;
    t->name = (char *)malloc(name_size * sizeof(char));
    strcpy(t->name, name);
    return t;
}

/**
 * Frees a Teacher allocated by createTeacher().
 * @param[in,out] t the address of the Teacher object.
 * @return Nothing.
 */
void freeTeacher(Teacher **t)
{
    Teacher *tmp = *t;
    free(tmp->name);
    free(tmp);
    *t = NULL;
}

/**
 * Prints a Teacher object to the console.
 * @param[in] t a Teacher object.
 * @return Nothing.
 */
void displayTeacher(Teacher *t)
{
    printf("<Teacher>(id: %d, name: '%s', age: %d)", t->id, t->name, t->age);
}

/**
 * Reads a Teacher's details from user.\n
 * @note It doesn't read the id from the user that needs to be implemented seperately.
 * @param[in] id the id of the Teacher.
 * @return a Teacher object.
 */
Teacher *readTeacher(int id)
{
    char name_buf[INPUT_SIZE], age_buf[INPUT_SIZE];

    // reads the name from user and stores it in a buffer.
    printf("Enter Teacher's Name: ");
    fgets(name_buf, INPUT_SIZE, stdin);
    name_buf[strcspn(name_buf, "\r\n")] = '\0';

    // reads the age from user and stores it in a buffer.
    printf("Enter Teacher's Age: ");
    fgets(age_buf, INPUT_SIZE, stdin);
    age_buf[strcspn(age_buf, "\r\n")] = '\0';
    // converts the buffer to an integer.
    int age = strtol(age_buf, NULL, 10);

    return createTeacher(id, age, name_buf);
}

/**
 * Updates a Teacher's details from user.\n
 * @note It doesn't change the id of the Teacher.
 * @param[in] t a Teacher object.
 * @return Nothing.
 */
void updateTeacher(Teacher *t)
{
    char name_buf[INPUT_SIZE], age_buf[INPUT_SIZE];

    // reads the name from user and stores it in a buffer.
    printf("Enter new Teacher Name: ");
    fgets(name_buf, INPUT_SIZE, stdin);
    name_buf[strcspn(name_buf, "\r\n")] = '\0';

    // reads the age from user and stores it in a buffer.
    printf("Enter new Teacher Age: ");
    fgets(age_buf, INPUT_SIZE, stdin);
    age_buf[strcspn(age_buf, "\r\n")] = '\0';
    // converts the buffer to an integer.
    int age = strtol(age_buf, NULL, 10);

    t->age = age;
    free(t->name);
    int name_size = strlen(name_buf) + 1;
    t->name = (char *)malloc(name_size * sizeof(char));
    strcpy(t->name, name_buf);
}

// ==========================================================================================
// ============================== LinkedList Functions ======================================
// ==========================================================================================

/**
 * Allocates and Creates a ListNode containing a Teacher object.
 * @param[in] t a Teacher object.
 * @return a ListNode object.
 */
ListNode *createNode(Teacher *t)
{
    ListNode *tmp = (ListNode *)malloc(sizeof(ListNode));
    tmp->t = t;
    tmp->nextNode = NULL;
    return tmp;
}

/**
 * Frees a ListNode allocated by createNode().
 * @param[in,out] node the address of the ListNode object.
 * @return Nothing.
 */
void freeNode(ListNode **node)
{
    ListNode *tmp = *node;
    freeTeacher(&tmp->t);
    free(tmp);
    *node = NULL;
}

/**
 * Inserts a new ListNode at the head of the List object.
 * @param[in] list a List object.
 * @param[in] t a Teacher object.
 * @return Nothing.
 */
void insert(List *list, Teacher *t)
{
    ListNode *newNode = createNode(t);
    newNode->nextNode = list->head;
    list->head = newNode;
    list->length++;
}

/**
 * Searches a Teacher List for the Teacher with the specified id.
 * @param[in] list a List object.
 * @param[in] id the id of the Teacher.
 * @return ListNode object -> if it is found.
 * @return NULL -> if it isn't found.
 */
ListNode *searchByID(List *list, int id)
{
    ListNode *current = list->head;
    while (current != NULL)
    {
        if (current->t->id == id)
            return current;
        current = current->nextNode;
    }
    return NULL;
}

/**
 * Checks if the id is used in a List object.
 * @param[in] list a List object.
 * @param[in] id the id of the Teacher.
 * @return true -> if it isn't used. (unique)
 * @return false -> if it is used. (not unique)
 */
bool isUniqueID(List *list, int id)
{
    if (searchByID(list, id))
        return false;
    return true;
}

/**
 * Searches for the Teacher with specified id and displays it.
 * @param[in] list a List object.
 * @param[in] id the id of the Teacher.
 * @return 0 -> no errors.
 * @return 1 -> couldn't find Teacher object.
 */
int displayByID(List *list, int id)
{
    ListNode *node = searchByID(list, id);
    if (!node)
    {
        fprintf(stderr, "Error: Teacher with id=%d couldn't be found.\n", id);
        return 1;
    }
    displayTeacher(node->t);
    printf("\n");
    return 0;
}

/**
 * Searches for the Teacher with specified id and updates it's details.
 * @param[in] list a List object.
 * @param[in] id the id of the Teacher.
 * @return 0 -> no errors.
 * @return 1 -> couldn't find Teacher object.
 */
int updateById(List *list, int id)
{
    ListNode *node = searchByID(list, id);
    if (!node)
    {
        fprintf(stderr, "Error: Teacher with id=%d couldn't be found.\n", id);
        return 1;
    }
    updateTeacher(node->t);
    return 0;
}

/**
 * Searches for the Teacher with specified id and deletes it.
 * @param[in] list a List object.
 * @param[in] id the id of the Teacher.
 * @return 0 -> no errors.
 * @return 1 -> couldn't find Teacher object.
 * @return -1 -> the List provided is empty.
 */
int deleteByID(List *list, int id)
{
    ListNode *current = list->head;
    // Empty List, head points to NULL.
    if (current == NULL)
    {
        fprintf(stderr, "Error: List is Empty. Can't delete from Empty List.\n");
        return -1;
    }
    // If the first ListNode is the needed one.
    if (current->t->id == id)
    {
        ListNode *deleteNode = current;
        list->head = deleteNode->nextNode;
        freeNode(&deleteNode);
        list->length--;
        return 0;
    }
    // Loop through List to find the needed one.
    while (current->nextNode != NULL && current->nextNode->t->id != id)
    {
        current = current->nextNode;
    }
    // Reached end without finding the teacher.
    if (current->nextNode == NULL)
    {
        fprintf(stderr, "Error: Teacher with id=%d couldn't be found.\n", id);
        return 1;
    }
    // Remove the node.
    ListNode *deleteNode = current->nextNode;
    current->nextNode = deleteNode->nextNode;
    freeNode(&deleteNode);
    list->length--;
    return 0;
}

/**
 * Prints a Teacher List to the console.
 * @param[in] list a List object.
 * @return Nothing.
 */
void displayList(List *list)
{
    ListNode *current = list->head;
    printf("[\n");
    while (current != NULL)
    {
        displayTeacher(current->t);
        printf(",\n");
        current = current->nextNode;
    }
    printf("], length: %d\n", list->length);
}

/**
 * Adds 'n' Teacher objects to the beginning of a List object.
 * @param list a List object.
 * @return Nothing.
 */
void addToList(List *list)
{
    int n = 0;
    do
    {
        printf("Enter how many Teachers you wanna add: ");
        scanf("%d", &n);
        getchar();
    } while (n < 0);

    if (n == 0)
        return;

    for (int i = 0; i < n; i++)
    {
        int ID = 0;
        do
        {
            printf("Enter the ID of the teacher: ");
            scanf("%d", &ID);
            getchar();
        } while (!isUniqueID(list, ID));
        insert(list, readTeacher(ID));
    }
}

/**
 * Allocates and Creates a new List object.
 * @return a List object.
 */
List *createList()
{
    List *tmp = (List *)malloc(sizeof(List));
    tmp->head = NULL;
    tmp->length = 0;
    return tmp;
}

/**
 * Frees a List allocated by createList().
 * @param list the address of the List object.
 * @return Nothing.
 */
void freeList(List **list)
{
    ListNode *current = (*list)->head;
    while (current != NULL)
    {
        ListNode *deleteNode = current;
        current = current->nextNode;
        freeNode(&deleteNode);
    }
    free(*list);
    *list = NULL;
}

// ==================================================================================
// ================================= Main Program ===================================
// ==================================================================================

/**
 * Clears the screen.
 */
#ifdef _WIN32
void clear()
{
    system("cls");
}
#else // IF NOT _WIN32
void clear()
{
    system("clear");
}
#endif

/**
 * Reads an ID from the user.
 * @return An id.
 */
int getID()
{
    int userID;
    printf("Please Enter Teacher's ID: ");
    scanf("%d", &userID);
    getchar();
    return userID;
}

/**
 * Main entry point of the program.
 */
int main(void)
{
    List *tList = createList();
    bool End = false;
    while (!End)
    {
        clear();
        printf("Menu:\n");
        printf("----------------------------\n");
        printf("1) Add to the Teacher's List.\n");
        printf("2) Search Teacher's List for an ID.\n");
        printf("3) Read about a specific Teacher.\n");
        printf("4) Update a specific Teacher's info.\n");
        printf("5) Remove a specific Teacher from the List.\n");
        printf("6) Display the Teacher's List.\n");
        printf("0) Exit.\n");

        int choice;
        do
        {
            printf(": ");
            scanf("%d", &choice);
            getchar();
        } while (choice < 0 || choice > 6);

        if (choice != 0)
            clear();
        switch (choice)
        {
        case 0:
            End = true;
            break;
        case 1:
            printf("Add to the Teacher's List:\n");
            printf("----------------------------\n");
            addToList(tList);
            break;
        case 2:
            printf("Search Teacher's List for an ID:\n");
            printf("----------------------------------\n");
            if (searchByID(tList, getID()))
                printf("The Teacher exist!\n");
            else
                printf("The Teacher doesn't exist :(\n");
            break;
        case 3:
            printf("Read about a specific Teacher:\n");
            printf("--------------------------------\n");
            displayByID(tList, getID());
            break;
        case 4:
            printf("Update a specific Teacher's info:\n");
            printf("-----------------------------------\n");
            updateById(tList, getID());
            break;
        case 5:
            printf("Remove a specific Teacher from the List:\n");
            printf("------------------------------------------\n");
            deleteByID(tList, getID());
            break;
        case 6:
            printf("Display the Teacher's List:\n");
            printf("-----------------------------\n");
            displayList(tList);
            break;
        }
        if (choice != 0)
        {
            // Pauses the program to see output.
            printf("Press Enter to continue...");
            getchar();
        }
    }
    freeList(&tList);
    printf("Thank you for using my program! <3\n");
    return 0;
}