#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedListLib.h"

listElement* newNode(char* name, char* lastname, int age) {
    listElement* temp = (listElement*)malloc(sizeof(listElement));
    strcpy(temp->firstName, name);
    strcpy(temp->lastName, lastname);
    temp->age = age;
    temp->nextElem = NULL;
    return temp;
}

void addListElem(listElement *start)
{

    listElement *new;
    new = (listElement *)malloc(sizeof(listElement));
    if (new == NULL)
    {
        printf("can't reserve storage.\n");
        return;
    }

    listElement *currElem = start;
    while (currElem->nextElem != NULL)
        currElem = currElem->nextElem; // get last elem in list
    currElem->nextElem = new;          // add new to the end of list
    new->nextElem = NULL;

    /* fill data in new element */
    printf("Please enter last name: \n");
    scanf("%s", new->lastName);
    printf("Please enter first name: \n");
    scanf("%s", new->firstName);
    printf("Please enter age: \n");
    scanf("%d", &(new->age));
}

void printList(listElement *start)
{

    if ((start->nextElem == NULL))
        printf("List is empty.\n");
    else
    {
        int i = 0;
        listElement *currElem = start;
        printf("\ncurrent list:\n\n");
        do
        {
            currElem = currElem->nextElem;
            printf("%d", i);
            i++;
            printf("\t last name: %s\n", currElem->lastName);
            printf("\t first name: %s\n", currElem->firstName);
            printf("\t age: %d\n\n", currElem->age);
        } while (currElem->nextElem != NULL);
    }
}

void delListElem(listElement *start)
{
    int delete_position;
    listElement* currElem = start;
    listElement* next;

    printList(start);
    if (start->nextElem != NULL) {
        printf("Which element should be deleted?\n");
        scanf("%d", &delete_position);
        delete_position++;
    }
    else {
        printf("List is empty.\n");
        return;
    }
    if ((delete_position < 1) && (delete_position > (getLenOfList(start)))) {
        printf("Position is out of bounds.\n");
        return;
    }

    for (int i = 0; currElem != NULL && i < delete_position - 1; i++)
        currElem = currElem->nextElem;
    if (currElem == NULL || currElem->nextElem == NULL)
        return;

    next = currElem->nextElem->nextElem;

    free(currElem->nextElem);

    currElem->nextElem = next;
}

void delList(listElement *start)
{
    listElement* currElem = start;
    listElement* next;
    while (currElem != NULL) {
        next = currElem->nextElem;
        free(currElem);
        currElem = next;
    }
    start = (listElement*)malloc(sizeof(listElement));
    start->nextElem = NULL;
    printf("The list has been deleted.\n");

}

int getLenOfList(listElement *start)
{ // we use this for save list fcn

    int counter = 0;
    listElement *currElem = start;
    while (currElem->nextElem != NULL)
    { // get last elem in list
        currElem = currElem->nextElem;
        counter++;
    }
    return counter;
}

void saveList(listElement* start)
{
    FILE* filePointer;
    listElement* currElem = start;
    char file_name[256]; //maximum characterlength for filename
    int i = 0;
    if (start->nextElem == NULL) {
        printf("The list is empty - there's nothing to be saved.\n");
    }
    else {
        printf("Enter how you'd like to name your file: ");
        scanf("%s", &file_name);
        strcat(file_name, ".txt");

        filePointer = fopen(file_name, "w");

        if (filePointer == NULL) {
            printf("Failed to create file.\n");
        }
        else {
            do
            {
                currElem = currElem->nextElem;
                fprintf(filePointer, "%s\n", currElem->lastName);
                fprintf(filePointer, "%s\n", currElem->firstName);
                fprintf(filePointer, "%d\n", currElem->age);
            } while (currElem->nextElem != NULL);
            fclose(filePointer);
            printf("The list was saved under the filename '%s'.\n", file_name);
        }

    }
    
}

void loadList(listElement *start)
{
    FILE* filePointer;
    char file_name[256];
    system("dir *.txt");
    printf("\nWhich list would you like to load? (Only filename, without .txt): ");
    scanf("%s", &file_name);

    strcat(file_name, ".txt");

    filePointer = fopen(file_name, "r");
    if (filePointer == NULL) {
        printf("Could not open file\n");
        return start;
    }
    char firstName[50], lastName[50];
    int age;

    listElement* tail = start;
    while (tail != NULL && tail->nextElem != NULL) {
        tail = tail->nextElem;
    }

    while (fscanf(filePointer, "%s\n%s\n%d", lastName, firstName, &age) != EOF) {
        listElement* temp = newNode(firstName, lastName, age);

        if (start == NULL) {
            start = tail = temp;
        }
        else {

            tail->nextElem = temp;
            tail = temp;
        }
    }
    fclose(filePointer);
    printList(start);

}

void exitFcn(listElement* start)
{
    char answer;
    int flag = 0;

    while (flag == 0) {
        printf("Would you like to save your list before exiting?\n('y' for yes, 'n' for no): ");
        scanf(" %c", &answer);
        if (answer == 'y' || answer == 'n') {
            flag++;
        }
        else {
            printf("Invalid answer.\n");
        }
    }
    if (answer == 'y') {
        saveList(start);
    }
    printf("Exiting the program.");
    return;


}

void sortList(listElement *start)
{

    printf("\n>>sortList fcn is tbd.\n\n");
}

void stringToLower(char *string)
{

    printf("\n>>stringToLower fcn is tbd.\n\n");
}


/* #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

struct Element {
  char name1[MAX_NAME_LENGTH];
  char name2[MAX_NAME_LENGTH];
  int value;
  struct Element *next;
};

void read_from_file(struct Element *head, const char *file_name) {
  FILE *fp;
  fp = fopen(file_name, "r");
  if (fp == NULL) {
    printf("Error opening file\n");
    exit(1);
  }

  struct Element *current = head;
  char name1[MAX_NAME_LENGTH];
  char name2[MAX_NAME_LENGTH];
  int value;
  while (fscanf(fp, "%s %s %d", name1, name2, &value) == 3) {
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = (struct Element *) malloc(sizeof(struct Element));
    strcpy(current->next->name1, name1);
    strcpy(current->next->name2, name2);
    current->next->value = value;
    current->next->next = NULL;
  }

  fclose(fp);
}

*/