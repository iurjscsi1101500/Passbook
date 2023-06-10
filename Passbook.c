#include <stdio.h>
#include <string.h>

typedef struct {
    char name[256];
    char last_name[256];
    char email[256];
    char phone_number[256];
    char dob[256];
    char gender;
    char password[256];
} User;

void getName(User *user) {
    printf("----------------\n");
    printf("Enter First name: ");
    scanf("%255s", user->name);
}

void getLastname(User *user) {
    printf("Enter last name: ");
    scanf("%255s", user->last_name);
}

void getEmail(User *user) {
    printf("Enter email: ");
    scanf("%255s", user->email);
}

void getPhoneNumber(User *user) {
    printf("Enter phone number: ");
    scanf("%255s", user->phone_number);
}

void getDOB(User *user) {
    printf("Enter dob: ");
    scanf("%255s", user->dob);
}

void getGender(User *user) {
    printf("Enter gender (M/F): ");
    scanf(" %c", &user->gender);
}

void getPassword(User *user) {
    printf("Enter password: ");
    scanf("%255s", user->password);
    printf("----------------\n");
}

void displayUser(const User *user) {
    char password1[256];
    printf("Enter password: ");
    scanf("%255s", password1);

    if (strcmp(password1, user->password) != 0) {
        printf("Error: Password is incorrect\n");
        return;
    }

    if (user->name[0] == '\0' || user->last_name[0] == '\0' || user->email[0] == '\0' ||
        user->phone_number[0] == '\0' || user->dob[0] == '\0' || user->gender == '\0') {
        printf("Error: User data is empty\n");
        return;
    }

    printf("--------------------------------\n");
    printf("First Name: %s\n", user->name);
    printf("Last Name: %s\n", user->last_name);
    printf("Email: %s\n", user->email);
    printf("Phone Number: %s\n", user->phone_number);
    printf("DOB: %s\n", user->dob);
    printf("Gender: %c\n", user->gender);
    printf("--------------------------------\n");
}

void modify(User *user) {
    char pass[256];
    printf("Enter password: ");
    scanf("%255s", pass);

    if (strcmp(pass, user->password) != 0) {
        printf("Error: Password is incorrect\n");
        return;
    }

    printf("Enter what you want to modify (N for Name, L for Last name, E for Email, H for Phone, D for DOB, G for Gender): ");
    char option;
    scanf(" %c", &option);

    switch (option) {
        case 'N':
            getName(user);
            break;
        case 'L':
            getLastname(user);
            break;
        case 'E':
            getEmail(user);
            break;
        case 'H':
            getPhoneNumber(user);
            break;
        case 'D':
            getDOB(user);
            break;
        case 'G':
            getGender(user);
            break;
        default:
            printf("Invalid option\n");
            break;
    }
}

int main() {
    User user;
    int choice;

    while (1) {
        printf("----------------\n");
        printf("\nSimple Database\n");
        printf("\n");
        printf("1. Create Account\n");
        printf("\n");
        printf("2. Display Account\n");
        printf("\n");
        printf("3. Modify Account\n");
        printf("\n");
        printf("4. Exit\n");
        printf("----------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                getName(&user);
                getLastname(&user);
                getEmail(&user);
                getPhoneNumber(&user);
                getDOB(&user);
                getGender(&user);
                getPassword(&user);
                break;
            case 2:
                displayUser(&user);
                break;
            case 3:
                modify(&user);
                break;
            case 4:
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
