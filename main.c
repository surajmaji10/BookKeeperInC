#include "common.h"
#include "users.h"
#include "depts.h"
#include "utility.h"
#include <unistd.h>

#include <mysql/mysql.h>

void test(){
    // displayDepartments(DEPTS);
    printf("=========Hello User! Welcome to the book libraray============\n");

    FILE* fptr = fopen("users_info.bin", "rb+");

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


    char** depts = getAllDepartments();
    //printf("getting adress %p\n", depts);
    displayDepartments(depts);
}

int queryExecutor(){
      MYSQL *conn;                                                                                       

   char req[] = "INSERT INTO Users (UserID, Age, Name, Dept) VALUES (111, 25, \'Yoyo Maji\', \'CS\');";
  if ((conn = mysql_init(NULL)) == NULL)                                                             
  {                                                                                                  
    fprintf(stderr, "Could not init DB\n");                                                 
    return EXIT_FAILURE;                                                                             
  }                                                                                                  
  if (mysql_real_connect(conn, "localhost", "root", "majiak", "hello_akash", 0, NULL, 0) == NULL)             
  {                                                                                                  
    fprintf(stderr, "DB Connection Error\n");                                                        
    return EXIT_FAILURE;                                                                             
  }                                                                                                  
  if (mysql_query(conn,req) != 0)                   
  {                                                                                                  
    fprintf(stderr, "Query Failure\n");                                                              
    return EXIT_FAILURE;                                                                             
  }                                                                                                  
  mysql_close(conn);                                                                                 
  return EXIT_SUCCESS;  
}

void showGreetingOnStart(){
    printf("******************Hello User! Welcome to the book libraray******************\n");
}

void showMenuOptions(){
    //printf("0. Exit (Press 0):");
    drawStar(50);
    printf("Please Select One of these Options(Press Ctrl+C to exit):\n");
    drawStar(50);
    printf("0. Exit (Press 0):\n");
    printf("1. Login into libraray as user  (Press 1):\n");
    printf("2. Login into libraray as admin (Press 2):\n");
    printf("3. View library details (Press 2):\n");
    printf("4. View all departmentwise users info (Press 4):\n");
    drawStar(50);
}

void exitFromHere(){
    printf("\nThank You! Vist Again :)");
    exit(0);
}

void adminLogin(){

    printf("\nPlease Enter admin credentials: ");

    char adminName[20] = {0};
    char *adminPass = malloc(20);
    memset(adminPass, 0, 20);

    printf("Enter Admin Name: ");
    scanf("%s", adminName);
    getchar();

    //printf("Enter Admin Pass: ");
    //scanf("%s", adminPass);
    //getchar();
    adminPass = get_tty_password("Enter Admin Pass: ");
    
    

    printf("You entered:\nID:%s\nPASS:%s\n", adminName, adminPass);
    printf("You entered:\nID:%ld\nPASS:%ld\n", strlen(adminName), strlen(adminPass));
    printf("Login Success!\n");
    
}

void userLogin(){
    printf("\nPlease Enter User Credentials: ");
    
}
void doNothing(){

}
int chooseMenuOptionAndAct(){
    int option;
    printf("Your Choice: ");
    scanf("%d", &option);

    switch(option){
        case 0:
            exitFromHere();
            break;
        case 1:
            adminLogin();
            break;
        case 2:
            userLogin();
            break;
        case 3:
        case 4:
            doNothing();
            break;
        default:
            printf("Invalid Choice !");
            showMenuOptions();
            break;
            
    }

}



/*

Execute in terminal as
$ gcc *.c -lmysqlclient

*/

int main(){
    // test();
    //queryExecutor();
    //queryExecutor();
   // char req[] = "INSERT INTO Users (UserID, Age, Name, Dept) VALUES (111, 25, \'Yoyo Maji\', \'CS\');";
   // printf("%ld  %ld\n%s\n", strlen(req), sizeof(req), req);

   showGreetingOnStart();
   showMenuOptions();
   chooseMenuOptionAndAct();



}