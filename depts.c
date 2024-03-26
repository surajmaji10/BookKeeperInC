#include<string.h>
#include<stdio.h>
#include "constants.h"
#include "utility.h"
#include "depts.h"

void displayDepartments(char* listDept[]){
    if(listDept!= NULL){
        int n = NUM_DEPT;
        //printf("%d\n", strlen(list));
        printf("[");
        for(int i = 0; i <n-1; i++){
            printf("%s|", listDept[i]);
        }
        printf("%s]: ", listDept[n-1]);
    }
        
    else
        printf("Empty Department List Given.\n");

}

int checkValidDepartment(char* listDept[], char* deptInput){

    if(listDept != NULL && strlen(listDept) > 0){

        int found = 0;
        int n = NUM_DEPT;
        for(int i = 0; i < n; i++){
            //printf("%s\n", listDept[i]);
            convertToUpperCase(deptInput, -1);
           // printf("%s\n", deptInput);
            if(strcmp(listDept[i], deptInput) == 0){
                found = 1;
                return found;
            }
        }
        return found;

    }

    return -1;

}

char** getAllDepartments(){
    //printf("returning adress %p\n", DEPTS);
    return DEPTS;
}