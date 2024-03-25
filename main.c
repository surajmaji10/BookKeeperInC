#include "common.h"
#include "users.h"
#include "depts.h"

void test(){
    //displayDepartments(DEPTS);
}
int main(){

    printf("=========Hello User! Welcome to the book libraray============\n");

    FILE* fptr = fopen("users_data.bin", "rb+");

    User* newuser1 = createUserAndShowStatus();
    saveUserIntoFile(fptr, newuser1);
    getUserInfoFromFile(fptr, newuser1);

    User* newuser2 = createUserAndShowStatus();
    saveUserIntoFile(fptr, newuser2);
    getUserInfoFromFile(fptr, newuser2);

    User* newuser3 = createUserAndShowStatus();
    saveUserIntoFile(fptr, newuser3);
    getUserInfoFromFile(fptr, newuser3);

    printAllUserFromFile(fptr, NULL);


    test();

}
