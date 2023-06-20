#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define MAX_NAME_LENGTH 256
#define MAX_EMAIL_LENGTH 256
#define MAX_PHONE_LENGTH 256
#define MAX_DOB_LENGTH 256
#define MAX_PASSWORD_LENGTH 256
#define MAX_USERS 10
void file(){
    FILE *ptr;
    ptr = fopen("new_file.txt","r");
    if(ptr == NULL){
        printf("\n");
        printf("\n");
        printf("Error File dosent exist\nmaking file\n");
        sleep(3);
        system("touch new_file.txt");
        printf("Created File\n\n");
    }
}

typedef struct {
    char name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone_number[MAX_PHONE_LENGTH];
    char dob[MAX_DOB_LENGTH];
    char gender;
    char password[MAX_PASSWORD_LENGTH];
} User;

typedef struct {
    User users[MAX_USERS];
    int count;
} UserDatabase;

void getName(char *name) {
    printf("----------------\n");
    printf("Enter First name: ");
    fgets(name, MAX_NAME_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0'; // remove newline character
}

void getLastname(char *last_name) {
    printf("Enter last name: ");
    fgets(last_name, MAX_NAME_LENGTH, stdin);
    last_name[strcspn(last_name, "\n")] = '\0';
}

void getEmail(char *email) {
    printf("Enter email: ");
    fgets(email, MAX_EMAIL_LENGTH, stdin);
    email[strcspn(email, "\n")] = '\0';
}

void getPhoneNumber(char *phone_number) {
    printf("Enter phone number: ");
    fgets(phone_number, MAX_PHONE_LENGTH, stdin);
    phone_number[strcspn(phone_number, "\n")] = '\0';
}

void getDOB(char *dob) {
    printf("Enter Date Of Birth: ");
    fgets(dob, MAX_DOB_LENGTH, stdin);
    dob[strcspn(dob, "\n")] = '\0';
}

void getGender(char *gender) {
    printf("Enter gender (M/F): ");
    scanf(" %c", gender);
    getchar(); // consume the newline character
}

void getPassword(char *password) {
    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';
    printf("----------------\n");
}

bool validatePassword(const User *user, const char *password) {
    return strcmp(user->password, password) == 0;
}

bool isUserDataEmpty(const User *user) {
    return (user->name[0] == '\0' || user->last_name[0] == '\0' || user->email[0] == '\0' ||
            user->phone_number[0] == '\0' || user->dob[0] == '\0' || user->gender == '\0');
}

void displayUser(const User *user) {
    char password1[MAX_PASSWORD_LENGTH];
    printf("wont use database dat it will use program data\n");
    printf("Enter password: ");
    fgets(password1, sizeof(password1), stdin);
    password1[strcspn(password1, "\n")] = '\0';

    if (!validatePassword(user, password1)) {
        printf("Error: Password is incorrect\n");
        return;
    }

    if (isUserDataEmpty(user)) {
        printf("Error: User data is empty\n");
        return;
    }

    printf("--------------------------------\n");
    printf("First Name: %s\n", user->name);
    printf("Last Name: %s\n", user->last_name);
    printf("Email: %s\n", user->email);
    printf("Phone Number: %s\n", user->phone_number);
    printf("Date of birth: %s\n", user->dob);
    printf("Gender: %c\n", user->gender);
    printf("--------------------------------\n");
}

void modify(User *user) {
    FILE *fptr;
    fptr = fopen("new_file.txt","a");
    char pass[MAX_PASSWORD_LENGTH];
    printf("Enter password: ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0';
    if (!validatePassword(user, pass)) {
        printf("Error: Password is incorrect\n");
        return;
    }

    printf("Enter what you want to modify (N for Name, L for Last name, E for Email, H for Phone, D for Date of Birth, G for Gender): ");
    char option;
    scanf(" %c", &option);
    getchar(); // consume the newline character

    switch (option) {
        case 'N':
            getName(user->name);
            break;
        case 'L':
            getLastname(user->last_name);
            break;
        case 'E':
            getEmail(user->email);
            break;
        case 'H':
            getPhoneNumber(user->phone_number);
            break;
        case 'D':
            getDOB(user->dob);
            break;
        case 'G':
            getGender(&user->gender);
            break;
        default:
            printf("Invalid option\n");
            break;
    }
    fprintf(fptr, "MODIFYED:\n Name: %s\nLast name: %s\nEmail: %s\nPhone number: %s\nDate of birth: %s\nGender: %c\n\n",
            user->name, user->last_name, user->email, user->phone_number, user->dob, user->gender);
    fclose(fptr);
}

void printMenu() {
    printf("----------------\n");
    printf("\nSimple Database\n");
    printf("\n");
    printf("1. Create Account\n");
    printf("2. Login\n");
    printf("3. Display Account\n");
    printf("4. Modify Account\n");
    printf("5. Exit\n");
    printf("----------------\n");
    printf("Enter your choice: ");
}

void createAccount(UserDatabase *db) {
    FILE *fptr;
    fptr = fopen("new_file.txt","a");
    if (db->count == MAX_USERS) {
        printf("Error: Maximum number of users reached\n");
        return;
    }

    User *user = &db->users[db->count];

    getName(user->name);
    getLastname(user->last_name);
    getEmail(user->email);
    getPhoneNumber(user->phone_number);
    getDOB(user->dob);
    getGender(&user->gender);
    getPassword(user->password);
    fprintf(fptr, "Name: %s\nLast name: %s\nEmail: %s\nPhone number: %s\nDate of birth: %s\nGender: %c\n\n",
            user->name, user->last_name, user->email, user->phone_number, user->dob, user->gender);

    db->count++;
    fclose(fptr);
}

void login(UserDatabase *db) {
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("----------------\n");
    printf("Enter email: ");
    fgets(email, MAX_EMAIL_LENGTH, stdin);
    email[strcspn(email, "\n")] = '\0';

    printf("Enter password: ");
    fgets(password, MAX_PASSWORD_LENGTH, stdin);
    password[strcspn(password, "\n")] = '\0';
    printf("----------------\n");

    for (int i = 0; i < db->count; i++) {
        User *user = &db->users[i];
        if (strcmp(user->email, email) == 0 && strcmp(user->password, password) == 0) {
            displayUser(user);
            return;
        }
    }

    printf("Error: Invalid email or password\n");
}

int main() {
    file();
    UserDatabase db;
    db.count = 0;
    int choice;

    while (1) {
        printMenu();
        scanf("%d", &choice);
        getchar(); // consume the newline character

        switch (choice) {
            case 1:
                createAccount(&db);
                break;
            case 2:
                login(&db);
                break;
            case 3:
                displayUser(&db.users[0]);
                break;
            case 4:
                modify(&db.users[0]);
                break;
            case 5:
                printf("--------------------------------\n");
                printf("Thank You For Choosing Simple Database\n");
                printf("Goodbye\n");
                printf("--------------------------------\n");
                return 0;
            default:
                printf("Invalid choice\n");
                break;
        }
    }
}
