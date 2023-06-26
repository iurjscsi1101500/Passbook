#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define MIN_NAME_LENGTH 3
#define MAX_NAME_LENGTH 256
#define MIN_EMAIL_LENGTH 7
#define MAX_EMAIL_LENGTH 256
#define MAX_PHONE_LENGTH 11
#define MAX_DOB_LENGTH 11
#define MIN_PASSWORD_LENGTH 7
#define MAX_PASSWORD_LENGTH 256
#define MAX_USERS 10

typedef struct {
    char name[MAX_NAME_LENGTH];
    char last_name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char phone_number[MAX_PHONE_LENGTH];
    char dob[MAX_DOB_LENGTH];
    char gender;
    char password[MAX_PASSWORD_LENGTH];
    char username[MAX_NAME_LENGTH];
} User;

typedef struct {
    User users[MAX_USERS];
    int count;
} UserDatabase;

// Function to handle file creation if it doesn't exist
void fileHandling() {
    FILE *ptr = fopen("new_file.txt", "a");
    if (ptr == NULL) {
        printf("Error Opening file\nCreateing File\n");
        system("touch new_file.txt");
        printf("file created succsusfully\n");
        return;
    }
    fclose(ptr);
}

void get_gender(char *gender) {
    while (true) {
        printf("Enter gender (M/F): ");
        scanf(" %c", gender);
        getchar();
        if (*gender == 'M' || *gender == 'F') {
            break;
        } else {
            printf("Invalid option\n\n");
        }
    }
}

void get_Date_of_birth(char *dob) {
    while (true) {
        printf("Enter date of birth: ");
        fgets(dob, MAX_DOB_LENGTH, stdin);
        dob[strcspn(dob, "\n")] = '\0';
        if (strlen(dob) == MAX_DOB_LENGTH - 1) {
            break;
        } else {
            printf("Invalid option\n");
        }
    }
}

// Function to get username from the user
void getUsername(char *username) {
    while (true) {
        printf("Enter Username (above %d and below %d characters): ", MIN_NAME_LENGTH, MAX_NAME_LENGTH);
        fgets(username, MAX_NAME_LENGTH, stdin);
        username[strcspn(username, "\n")] = '\0';

        if (strlen(username) >= MIN_NAME_LENGTH && strlen(username) <= MAX_NAME_LENGTH) {
            break;
        } else {
            printf("Invalid name length. Please try again.\n");
        }
    }
}

// Function to get first name from the user
void getName(char *name) {
    while (true) {
        printf("Enter First name (above %d and below %d characters): ", MIN_NAME_LENGTH, MAX_NAME_LENGTH);
        fgets(name, MAX_NAME_LENGTH, stdin);
        name[strcspn(name, "\n")] = '\0';

        if (strlen(name) >= MIN_NAME_LENGTH && strlen(name) <= MAX_NAME_LENGTH) {
            break;
        } else {
            printf("Invalid name length. Please try again.\n");
        }
    }
}

// Function to get last name from the user
void getLastname(char *last_name) {
    while (true) {
        printf("Enter last name (above %d and below %d characters): ", MIN_NAME_LENGTH, MAX_NAME_LENGTH);
        fgets(last_name, MAX_NAME_LENGTH, stdin);
        last_name[strcspn(last_name, "\n")] = '\0';

        if (strlen(last_name) >= MIN_NAME_LENGTH && strlen(last_name) <= MAX_NAME_LENGTH) {
            break;
        } else {
            printf("Invalid name length. Please try again.\n");
        }
    }
}

// Function to get email from the user
void getEmail(char *email) {
    while (true) {
        printf("Enter Email (above %d and below %d characters): ", MIN_EMAIL_LENGTH, MAX_EMAIL_LENGTH);
        fgets(email, MAX_EMAIL_LENGTH, stdin);
        email[strcspn(email, "\n")] = '\0';

        if (strlen(email) >= MIN_EMAIL_LENGTH && strlen(email) <= MAX_EMAIL_LENGTH) {
            break;
        } else {
            printf("Invalid email length. Please try again.\n");
        }
    }
}

// Function to get phone number from the user
void getPhoneNumber(char *phone_number) {
    while (true) {
        printf("Enter phone number (only %d digits): ", MAX_PHONE_LENGTH - 1);
        fgets(phone_number, MAX_PHONE_LENGTH, stdin);
        phone_number[strcspn(phone_number, "\n")] = '\0';

        if (strlen(phone_number) == MAX_PHONE_LENGTH-1) {
            break;
        } else {
            printf("Invalid phone number length. Please try again.\n");
        }
    }
}

// Function to get password from the user
void getPassword(char *password) {
    while (true) {
        printf("Enter Password (above %d and below %d characters): ", MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH - 1);
        fgets(password, MAX_PASSWORD_LENGTH, stdin);
        password[strcspn(password, "\n")] = '\0';

        if (strlen(password) >= MIN_PASSWORD_LENGTH && strlen(password) <= MAX_PASSWORD_LENGTH) {
            break;
        } else {
            printf("Invalid password length. Please try again.\n");
        }
    }
}

// Function to validate the password
bool validatePassword(const User *user, const char *password) {
    return strcmp(user->password, password) == 0;
}

// Function to check if user data is empty
bool isUserDataEmpty(const User *user) {
    if (user->name[0] == '\0' || user->last_name[0] == '\0' || user->email[0] == '\0' ||
        user->phone_number[0] == '\0' || user->dob[0] == '\0' || user->gender == '\0') {
        return true;
    }
    return false;
}

// Function to display user information (admin only)
void displayUser(const User *user) {
    FILE *file = fopen("new_file.txt", "r");
    if (file == NULL) {
        printf("Error: Failed to open file\n");
        return;
    }

    char password[MAX_PASSWORD_LENGTH];
    printf("Admin Enter Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (strcmp(password, "Atharvaa1101") != 0) {
        printf("Unauthorized access\n");
        fclose(file);
        return;
    }

    system("cat new_file.txt");

    fclose(file);
}

// Function to modify user information
void modify(User *user) {
    if (isUserDataEmpty(user)) {
        printf("Please create your account\n");
        return;
    }
    FILE *file = fopen("new_file.txt", "a");
    if (file == NULL) {
        printf("Error: Failed to open file\n");
        return;
    }

    char pass[MAX_PASSWORD_LENGTH];
    printf("Enter password: ");
    fgets(pass, sizeof(pass), stdin);
    pass[strcspn(pass, "\n")] = '\0';

    if (!validatePassword(user, pass)) {
        printf("Error: Password is incorrect\n");
        fclose(file);
        return;
    }

    printf("Enter what you want to modify (N for Name, L for Last name, E for Email, H for Phone, D for Date of Birth, G for Gender, U for Username): ");
    char option;
    scanf(" %c", &option);
    getchar();

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
            get_Date_of_birth(user->dob);
            break;
        case 'G':
            get_gender(&user->gender);
            break;
        case 'U':
            getUsername(user->username);
            break;
        default:
            printf("Invalid option\n");
            break;
    }

    fprintf(file, "\n\nMODIFIED:\nUsername: %s\nName: %s\nLast name: %s\nEmail: %s\nPhone number: %s\nDate of birth: %s\nGender: %c\n\n",
            user->username, user->name, user->last_name, user->email, user->phone_number, user->dob, user->gender);

    fclose(file);
}

// Function to create a new user account
void createAccount(UserDatabase *db) {
    if (db->count == MAX_USERS) {
        printf("Error: Maximum number of users reached\n");
        return;
    }

    User *user = &db->users[db->count];
    getName(user->name);
    getLastname(user->last_name);
    getEmail(user->email);
    getPhoneNumber(user->phone_number);
    get_Date_of_birth(user->dob);
    get_gender(&user->gender);
    getUsername(user->username);
    getPassword(user->password);

    if (isUserDataEmpty(user)) {
        printf("Error\n");
        return;
    }

    FILE *file = fopen("new_file.txt", "a");
    if (file == NULL) {
        printf("Error: Failed to open file\n");
        return;
    }

    fprintf(file, "\n\nName: %s\nLast name: %s\nEmail: %s\nPhone number: %s\nDate of birth: %s\nGender: %c\nUsername: %s\n\n",
            user->name, user->last_name, user->email, user->phone_number, user->dob, user->gender, user->username);

    fclose(file);

    db->count++;
}

// The main function
int main() {
    UserDatabase db;
    db.count = 0;
    fileHandling();

    while (true) {
        unsigned int time_set = 1;
        sleep(time_set);
        printf("----------------\n");
        sleep(time_set);
        printf("\nSimple Database\n");
        sleep(time_set);
        printf("\n");
        printf("1. Create Account\n");
        sleep(time_set);
        printf("2. Display Account (only admin)\n");
        sleep(time_set);
        printf("3. Modify Account\n");
        sleep(time_set);
        printf("4. Exit\n");
        sleep(time_set);
        printf("----------------\n");
        sleep(time_set);
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                createAccount(&db);
                break;
            case 2:
                displayUser(&db.users[0]);
                break;
            case 3:
                modify(&db.users[0]);
                break;
            case 4:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice\n");
                break;
        }
    }
}
