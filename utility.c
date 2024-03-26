#include "common.h"
#include "utility.h"

void drawDashDouble(int len){
    //printf("\n");
    for(int i = 0; i < len; i++){
        printf("%c", '=');
    }
    printf("\n");
}
void drawDashSingle(int len){
    //printf("\n");
    for(int i = 0; i < len; i++){
        printf("%c", '-');
    }
    printf("\n");
}
void drawStar(int len){
    //printf("\n");
    for(int i = 0; i < len; i++){
        printf("%c", '*');
    }
    printf("\n");
}

void drawChar(char ch, int len){
   // printf("\n");
    for(int i = 0; i < len; i++){
        printf("%c", ch);
    }
    printf("\n");
}

void convertToUpperCase(char source[], int len){
    if(len == -1){
        len = strlen(source);
    }

    for(int i = 0; i < len; i++){
        source[i] = toupper(source[i]);
    }

    return;
}

void convertToLowerCase(char source[], int len){
    if(len == -1){
        len = strlen(source);
    }

    for(int i = 0; i < len; i++){
        source[i] = tolower(source[i]);
    }

    return;
}