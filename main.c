#include "common.h"
#include "users.h"
#include "depts.h"

#include <mysql/mysql.h>

void test(){
    // displayDepartments(DEPTS);
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


    char** depts = getAllDepartments();
    //printf("getting adress %p\n", depts);
    displayDepartments(depts);
}

int queryExecutor(){
      MYSQL *conn;                                                                                       

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
  if (mysql_query(conn, 
"\
INSERT INTO Users (UserID, Age, Name, Dept)\
VALUES (111, 25, \'Yoyo Maji\', \'CS\');\
"
) != 0)                   
  {                                                                                                  
    fprintf(stderr, "Query Failure\n");                                                              
    return EXIT_FAILURE;                                                                             
  }                                                                                                  
  mysql_close(conn);                                                                                 
  return EXIT_SUCCESS;  
}


/*

Execute in terminal as
$ gcc *.c -lmysqlclient

*/

int main(){
    test();
}