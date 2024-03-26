#include "common.h"
#include "utility.h"
#include "depts.h"
#include "users.h"
#include <time.h>

int generateUniqueUserID(int n){

    int lower = 10000;
    int upper = 99999;
    int num = (rand() % 
        (upper - lower + 1)) + lower; 
        printf("%d ", num); 
    return num;

}

User* createNewUser(){
    
    char name[20];
    int age;
    char dept[20];
    char address[100];
    int numBooksIssued = 0;
    int semester = 1;
    int id;
    char confirm[4];

    getUserName(name);
    getUserAddress(address);

    do{ getUserAge(&age); }while(isValidAge(age) == 0);
    
    do{ getUserDept(dept); }while(checkValidDepartment(getAllDepartments(), dept) == 0);
    
    getUserConfirmation(confirm);

    convertToLowerCase(confirm, -1);
    convertToUpperCase(name, -1);
    convertToUpperCase(dept, -1);
    convertToUpperCase(address, -1);


    if(strcmp(confirm, "yes") == 0 || strcmp(confirm, "y") == 0){

        //generate unique id for the user
        id = generateUniqueUserID(5);

        printf("New User Created Successfully!\n");

        User* newuser = malloc(sizeof(User));
        memset(newuser, 0, sizeof(*newuser));

        strcpy(newuser->userName, name);
        strcpy(newuser->userDept, dept);
        newuser->userAge = age;
        newuser->userNumBooksIssued = numBooksIssued;
        newuser->userId = id;
        newuser->userSemester = semester;
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
    printf("The user details are:\n");
    drawDashSingle(50);
    printf("User Name            : %s\n", user->userName);
    printf("User Age             : %d\n", user->userAge);
    printf("User Dept            : %s\n", user->userDept);
    printf("User Books Issued    : %d\n", user->userNumBooksIssued);
    //printf("User ID    : %d\n", user->userId);
    drawDashDouble(50);
}

char* getUserInsertQuery(User* user){
    char *query = malloc(500);
    memset(query, 0, 500);
    char id[10] = {0};
    char age[4] = {0};
    
    snprintf(id, 10,"%d", user->userId);
    snprintf(age, 4,"%d", user->userAge);
    
    strcpy(query, "INSERT INTO Users_Info (UserID, Age, Name, Dept) VALUES (");
    strcat(query, id);
    strcat(query, ", ");
    strcat(query, age);
    strcat(query, ", ");
    strcat(query, "\'");
    strcat(query, user->userName);
    strcat(query, "\'");
    strcat(query, ", ");
    strcat(query, "\'");
    strcat(query, user->userDept);
    strcat(query, "\'");
    strcat(query, ");");

   // printf("\n%ld  %ld\n%s\n", strlen(query), sizeof(query), query);
   return query;
}

char* getAdminInsertQuery(int adminId, int adminAge, char* adminName, char* adminPass){
    char *query = malloc(500);
    memset(query, 0, 500);
    char id[10] = {0};
    char age[4] = {0};
    
    snprintf(id, 10,"%d", adminId);
    snprintf(age, 4,"%d", adminAge);
    
    strcpy(query, "INSERT INTO Admins_Info (AdminID, Age, Name, Pass) VALUES (");
    strcat(query, id);
    strcat(query, ", ");
    strcat(query, age);
    strcat(query, ", ");
    strcat(query, "\'");
    strcat(query, adminName);
    strcat(query, "\'");
    strcat(query, ", ");
    strcat(query, "\'");
    strcat(query, adminPass);
    strcat(query, "\'");
    strcat(query, ");");

   // printf("\n%ld  %ld\n%s\n", strlen(query), sizeof(query), query);
   return query;
}

void displayUserName(User* user){
     printf(
        "User: %s\n", user->userName    
     );
}

User* createNewUserAndShowStatus(){
    User* newuser = createNewUser();
    if(newuser != NULL){
        printf("New User: %s created successfully :)\n", newuser->userName);
        displayUserDetails(newuser);
        //getUserInsertQuery(newuser);
    }else{
        printf("Something went wrong :( \n");
    }
    return newuser;
}

void printUsersInfoFromFile(FILE* fptr, User* user){
        if(fptr == NULL){
            printf("\nInvalid File Pointer.\n");
            return;
        }

        drawDashDouble(50);
        printf("The All Users' Details:");
        drawDashSingle(50);

        fseek(fptr, 0, SEEK_SET);
        int size = (int)sizeof(User);
        char buffer[size];
        User* readUser = (User*)malloc(size);

        while(fread(readUser, size, 1, fptr) == 1)
             displayUserDetails(readUser);

        //fread(buffer, size, 1, fptr);
        //printf("size=>%d\ndata=>%d\n", size, (int)strlen(buffer));
        //User *readUser = (User*)buffer;
        //printf("The read in user is:\n");
        //displayUserDetails(readUser);
        drawDashDouble(50);    
        return;
}

void printUserInfoFromFile(FILE* fptr, User* user){
    if(fptr == NULL){
        printf("\nInvalid File Pointer.\n");
        return;
    }
    if(user == NULL){
        printUsersInfoFromFile(fptr, user);
        return;
    }else if(user != NULL){
        fseek(fptr, 0, SEEK_SET);
        int size = (int)sizeof(User);
        char buffer[size];
        User* readUser = (User*)malloc(size);

        drawDashSingle(50);

        while(fread(readUser, size, 1, fptr) == 1)
            if(memcmp(readUser, user, size) == 0)
                displayUserName(readUser);

        drawDashSingle(50);
        
        return;
    }
   
}

int saveUserIntoFile(FILE* fptr, User *user){

    //FILE* fptr = fopen("users_info.bin", "rb+");
    if(fptr != NULL){
        fseek(fptr, 0, SEEK_END);
        fwrite(user, sizeof(*user), 1, fptr);
        printf("Data saved!\n");
        return 1;
    }
    printf("Data NOT saved!\n");
    return 0;
}

char* getUserName(char name[]){
    //char name[20];
    printf("Enter new user name: ");
    gets(name);
    //getchar();
    return name;

}
char* getUserDept(char dept[]){
    printf("Enter new user department");
    displayDepartments(getAllDepartments());
    gets(dept);
    return dept;

}

char* getUserAddress(char addr[]){
    //char name[20];
    printf("Enter new user address: ");
    gets(addr);
    //getchar();
    return addr;

}
int getUserAge(int* page){
    printf("Enter new user age: ");
    scanf("%d", page);
    getchar();
    return *page;
}

char* getUserConfirmation(char confirm[]){
    printf("Are you sure to register the user? <yes|no>: ");
    gets(confirm);
    return confirm;
}

int isValidAge(int age){
    if(age < 18 || age > 65){
        return 0;
    }
    return 1;
}