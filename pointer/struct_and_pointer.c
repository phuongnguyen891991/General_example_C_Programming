#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LIST_SIZE   10
/*
struct _person {
    char* firstName;
    char* lastName;
    char* title;
    unsigned int age;
};
*/

typedef struct _person {
    char* firstName;
    char* lastName;
    char* title;
    unsigned int age;
} Person;

Person person;

int main() {
    Person *ptrperson;
    ptrperson = (Person*) malloc(sizeof(Person));
    ptrperson->firstName = (char*) malloc(strlen("Emily")+1);
    strcpy(ptrperson->firstName, "Emily");
    ptrperson->age = 23;

}
