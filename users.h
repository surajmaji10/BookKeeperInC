typedef struct User{
    char userName[20];
    char userDept[10];
    char userAddress[100];
   
    int userId;
    int userAge;
    int userNumBooksIssued;
    int userSemester;
} User;

User* createNewUser();
User* createNewUser();
void displayUserDetails(User* user);
char* getUserInsertQuery(User* user);
char* getAdminInsertQuery();
void displayUserName(User* user);
User* createNewUserAndShowStatus();
char* getUserName(char* name);
char* getUserDept(char* dept);
char* getUserAddress(char addr[]);
int getUserAge(int* page);
char* getUserConfirmation(char* confirm);
int isValidAge(int age);
int generateUniqueUserID();

int saveUserIntoFile(FILE* fptr, User* user);
int saveAdminIntoFile(int, int, char*, char*);
void printUsersInfoFromFile(FILE* fptr, User* user);
void printUserInfoFromFile(FILE* fptr, User* user);


