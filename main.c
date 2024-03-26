#include "common.h"
#include "users.h"
#include "depts.h"
#include "utility.h"
#include <unistd.h>
#define USER_LOGIN_SUCCESS 1000
#define ADMIN_LOGIN_SUCCESS 2000
#define USER_LOGIN_FAILURE -1000
#define ADMIN_LOGIN_FAILURE -2000
#define SUCCESS 1
#define FAILURE 0

#include <mysql/mysql.h>

int isValidAdmin(char* name, char* pass){

    FILE *fptr;

   // use appropriate location if you are using MacOS or Linux
   fptr = fopen("admins_info.txt","r+");

   if(fptr == NULL)
   {
      printf("Admin Info NOT Read From File!");   
      return 0;            
   }else{

    fseek(fptr, 0, SEEK_SET);
    //adminId, adminAge, adminName, adminPass
    int idFile, idAge;
    char nameFile[20];
    char passFile[20];

    while(fscanf(fptr, "%d", &idFile) != EOF){
        fgetc(fptr);
        fscanf(fptr, "%d", &idAge);
        fgetc(fptr);
        fscanf(fptr, "%s", nameFile);
        fgetc(fptr);
        fscanf(fptr, "%s", passFile);
        fgetc(fptr);

        //printf("Given:\n%s\n%s\n", name, pass);
        //printf("Found:\n%s\n%s\n", nameFile, passFile);
        if(strcmp(name, nameFile) == 0 && strcmp(pass, passFile) == 0){
            printf("Admin Validated!\n");
            return 1;
        }
    }
    

    // printf("Given:\n%s\n%s\n", name, pass);
    // printf("Found:\n%s\n%s\n", nameFile, passFile);
    // if(strcmp(name, nameFile) == 0 && strcmp(pass, passFile) == 0){
    //     printf("Admin Validated!\n");
    //     return 1;
    // }else{
        printf("Admin NOT Validated!\n");
        return 0;
    //}



    //return 1;

   }

    
}

int insertNewUserByAdmin(){
    // displayDepartments(DEPTS);
    printf("====Hello Admin! Please Enter New User Details====\n");

    FILE* fptr = fopen("users_info.bin", "rb+");

    User* newuser1 = createNewUserAndShowStatus();

    int savedToFile = saveUserIntoFile(fptr, newuser1);
    printUserInfoFromFile(fptr, newuser1);

    char* query = getUserInsertQuery(newuser1);
    int savedToDB =  saveUserIntoDB(query);

    //printUsersInfoFromFile(fptr, NULL);


    //char** depts = getAllDepartments();
    //printf("getting adress %p\n", depts);
   // displayDepartments(depts);

   if(savedToFile && savedToDB){
    printf("User Data Saved Into File & DB!\n");
    return 1;
   }else{
    printf("User Data NOT Saved Into File & DB!\n");
    return 0;
   }
}
int insertNewAdminByAdmin(){
    printf("====Hello Admin! Please Enter Admin Details====\n");
        int adminId;
        int adminAge;
        char* adminName = malloc(20);
        memset(adminName, 0, 20);
        char* adminPass = malloc(20);
        memset(adminPass, 0, 20);
        printf("Enter New Admin ID:");
        scanf("%d", &adminId);
        getchar();
        printf("Enter New Admin Age :");
        scanf("%d", &adminAge);
        getchar();
        printf("Enter New Admin Name :");
        scanf("%s", adminName);
        getchar();
        printf("Enter New Admin Password :");
        scanf("%s", adminPass);
        getchar();

    int savedToFile = saveAdminIntoFile(adminId, adminAge, adminName, adminPass);

    char* query = getAdminInsertQuery(adminId, adminAge, adminName, adminPass);
    int savedToDB =  saveAdminIntoDB(query);

   if(savedToDB && savedToFile){
        printf("Admin Data Saved Into File & DB!\n");
        return 1;
   }else{
        printf("Admin Data NOT Saved Into File & DB!\n");
        return 0;
   }

}

int saveAdminIntoDB(char* req){
    saveUserIntoDB(req);
}

int saveUserIntoDB(char* req){
      MYSQL *conn;                                                                                       

   //char req[] = "INSERT INTO Users (UserID, Age, Name, Dept) VALUES (111, 25, \'Yoyo Maji\', \'CS\');";
  if ((conn = mysql_init(NULL)) == NULL)                                                             
  {                                                                                                  
    fprintf(stderr, "Could not init DB\n");                                                 
    return FAILURE;                                                                             
  }                                                                                                  
  if (mysql_real_connect(conn, "localhost", "root", "majiak", "hello_akash", 0, NULL, 0) == NULL)             
  {                                                                                                  
    fprintf(stderr, "DB Connection Error\n");                                                        
    return FAILURE;                                                                             
  }                                                                                                  
  if (mysql_query(conn,req) != 0)                   
  {                                                                                                  
    fprintf(stderr, "Query Failure\n");                                                              
    return FAILURE;                                                                             
  }                                                                                                  
  mysql_close(conn);                                                                                 
  return SUCCESS;  
}

void showGreetingOnStart(){
    printf("***Hello User! Welcome to the BOOK LIBRARY :)****\n");
}

void showGreetingOnEnd(){
     printf("****Bye User! Visit Again :(****\n");
}

void showMenuOptions(){
    //printf("0. Exit (Press 0):");
    drawStar(50);
    printf("Please Select One of these Options(Press Ctrl+C to exit):\n");
    drawStar(50);
    printf("0. Exit (Press 0):\n");
    printf("1. Login into libraray as admin      (Press 1):\n");
    printf("2. Login into libraray as user       (Press 2):\n");
    printf("3. View library details              (Press 3):\n");
    printf("4. View all departmentwise users info(Press 4):\n");
    drawStar(50);
}

void exitFromHere(){
    printf("\nThank You! Vist Again :)");
    exit(0);
}

int adminLogin(){

    printf("\nPlease Enter Admin credentials:\n");

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
    
    

   // printf("You entered:\nID:%s\nPASS:%s\n", adminName, adminPass);
   // printf("You entered:\nID:%ld\nPASS:%ld\n", strlen(adminName), strlen(adminPass));

   if(isValidAdmin(adminName, adminPass)){
    printf("Admin Login Success!\n");
    return ADMIN_LOGIN_SUCCESS;

   }else{
    printf("Admin Login Failure!\n");
    return ADMIN_LOGIN_FAILURE;

   }
    
    
}

int userLogin(){

    printf("\nPlease Enter User credentials:\n");

    char userName[20] = {0};
    char *userPass = malloc(20);
    memset(userPass, 0, 20);

    printf("Enter Admin Name: ");
    scanf("%s", userPass);
    getchar();

    //printf("Enter User Pass: ");
    //scanf("%s", userPass);
    //getchar();
    userPass = get_tty_password("Enter User Pass: ");
    
    
   
   // printf("You entered:\nID:%s\nPASS:%s\n", userName, userPass);
   // printf("You entered:\nID:%ld\nPASS:%ld\n", strlen(userName), strlen(userPass));
    printf("User Login Success!\n");
    return USER_LOGIN_SUCCESS;
    
}
void doNothing(){
    printf("\nI have nothing to do!\n");
    exit(0);
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
            return adminLogin();
            break;
        case 2:
            return userLogin();
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

int deleteExistingUserByAdmin(){
    return 0;
}

int doUponUserLoginSuccess(){
    return 0;
}

int doUponAdminLoginSuccess(){

    //insertNewUserByAdmin();

    drawStar(50);
    printf("Admin! Please Select One of these Options(Press Ctrl+C to exit):\n");
    drawStar(50);
    printf("0. Exit                                        (Press 0):\n");
    printf("1. Insert into libraray a new user             (Press 1):\n");
    printf("2. Delete from libraray an existing user       (Press 2):\n");
    printf("3. Insert into libraray a new admin            (Press 3):\n");
    printf("4. View user details                           (Press 4):\n");
    printf("5. View admin details                          (Press 5):\n");
    drawStar(50);

    printf("Your Choice: ");
    int choice;
    scanf("%d", &choice);
    getchar();

    switch(choice){
        case 0:
            exit(0);
        case 1:
            return insertNewUserByAdmin();
            break;
        case 2:
            return deleteExistingUserByAdmin();
            break;
        case 3:
            return insertNewAdminByAdmin();
            break;
        default:
           doNothing();
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
   int result = chooseMenuOptionAndAct();
   switch(result){
    case USER_LOGIN_SUCCESS:
            doUponUserLoginSuccess();
            break;
    case ADMIN_LOGIN_SUCCESS:
            doUponAdminLoginSuccess();
            break;
    case USER_LOGIN_FAILURE:
    case ADMIN_LOGIN_FAILURE:
    default:
        doNothing();

     showGreetingOnEnd();   
   }



}