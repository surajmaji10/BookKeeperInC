#include<string.h>
#include<stdio.h>
#include "utility.h"

void displayDepartments(char* listDept[]){
    if(listDept!= NULL){
        int n = (int)strlen(listDept);
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
        int n = (int)strlen(listDept);
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