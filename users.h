typedef struct User{
    char userName[20];
    int userAge;
    char userDept[10];
    int userNumBooksIssued;
    int userId;
} User;

User* createUser();
User* createUser();
void displayUserDetails(User* user);
void displayUserInsertQuery(User* user);
void displayUserName(User* user);
User* createUserAndShowStatus();
char* getUserName(char* name);
char* getUserDept(char* dept);
int getUserAge(int* page);
char* getUserConfirmation(char* confirm);
int isValidAge(int age);

int saveUserIntoFile(FILE* fptr, User* user);
void printAllUserFromFile(FILE* fptr, User* user);
void getUserInfoFromFile(FILE* fptr, User* user);


