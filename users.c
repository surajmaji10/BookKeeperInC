#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "utility.c"
#include "depts.c"

typedef struct User{
    char userName[20];
    int userAge;
    char userDept[10];
    int userNumBooksIssued;
} User;

User* createUser(){
    
    char name[20];
    int age;
    char dept[20];
    int numBooksIssued;

    char confirm[4];

    printf("Enter new user name: ");
    gets(name);
    //getchar();

    printf("Enter new user age: ");
    scanf("%d", &age);
    getchar();

    printf("Enter new user department");
    displayDepartments(DEPTS);
    gets(dept);
    //getchar();

    printf("Are you sure to register the user? <yes|no>: ");
    gets(confirm);
    //getchar();

    convertToLowerCase(confirm, -1);
    convertToUpperCase(name, -1);
    convertToUpperCase(dept, -1);


    if(strcmp(confirm, "yes") == 0 || strcmp(confirm, "y") == 0){

        printf("New User Created Successfully!\n");
        User* newuser = malloc(sizeof(User));
        strcpy(newuser->userName, name);
        strcpy(newuser->userDept, dept);
        newuser->userAge = age;
        newuser->userNumBooksIssued = 0;
        return newuser;

    }else if(strcmp(confirm, "no") == 0 || strcmp(confirm, "n") == 0){

        printf("New User NOT Created!\n");
        return NULL;

    }else{
        printf("Invalid Input!");
        return NULL;
    }

}

void displayUserDetails(User* user){
    drawDashDouble(50);
    printf("The user details are:");
    drawDashSingle(50);
    printf("User Name            : %s\n", user->userName);
    printf("User Age             : %d\n", user->userAge);
    printf("User Dept            : %s\n", user->userDept);
    printf("User Books Issued    : %d\n", user->userNumBooksIssued);
    drawDashDouble(50);
}

void createUserAndShowStatus(){
    User* newuser = createUser();
    if(newuser != NULL){
        printf("New User: %s created successfully :)\n", newuser->userName);
        displayUserDetails(newuser);

    }else{
        printf("Something went wrong :( \n");
    }
}