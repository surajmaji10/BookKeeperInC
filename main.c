#include<stdio.h>
#include "users.c"
int main(){
    printf("=========Hello User! Welcome to the book libraray============\n");

    User* newuser = createUser();
    if(newuser != NULL){
        printf("New User: %s created successfully :)\n", newuser->userName);
        displayUserDetails(newuser);

    }else{
        printf("Something went wrong :( \n");
    }

}