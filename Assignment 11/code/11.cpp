#include <iostream>
#include <fstream>
#include <cstring>
using namespace::std;

struct Member
{
    char email[40];
    char password[24];
    char IDNumber[12];
    char name[12];
    char phone[12];
};

void loadMemberInfo(ifstream& inMemberFile, Member memberDetails[], int& numMembers);

// input an integer from the keyboard, and
// returns the integer if it belongs to [ begin, end ], returns -1 otherwise.
int inputAnInteger(int begin, int end);

void login(Member memberDetails[], int numMembers);

// returns true if there is a member
// whose email and password are equal to the specified email and password, respectively
bool legal(char email[], char password[], Member memberDetails[], int numMembers, int& recordNumber);

void accountInfor(Member memberDetails[], int numMembers, int recordNumber);

void newMember(Member memberDetails[], int& numMembers);

// returns true if there is a member whose IDNumber is equal to newIDNumber
bool existingID(char newIDNumber[], Member memberDetails[], int& numMembers);

// returns true if there is a member whose email is equal to newEmail
bool existingEmail(char newEmail[], Member memberDetails[], int& numMembers);

void saveMemberInfo(ofstream& outMemberFile, Member memberDetails[], int numMembers);

int main()
{
    Member memberDetails[100] = { "", "", "", "", "" };
    int numMembers = 0;

    ifstream inMemberFile;
    ofstream outMemberFile;

    loadMemberInfo(inMemberFile, memberDetails, numMembers);

    cout << "Welcome to Vieshow Cinemas member system\n\n";

    int choice;

    while (true)
    {
        cout << "Enter your choice:" << endl;
        cout << "1. Sign In\n";
        cout << "2. New Member\n";
        cout << "3. Sign Out\n? ";

        choice = inputAnInteger(1, 3);
        cout << endl;

        switch (choice)
        {
        case 1:
            login(memberDetails, numMembers);
            break;

        case 2:
            newMember(memberDetails, numMembers);
            break;

        case 3:
            saveMemberInfo(outMemberFile, memberDetails, numMembers);
            cout << "Thank you...\n\n";
            system("pause");
            return 0;

        default:
            cout << "Input Error!\n\n";
            break;
        }
    }

    system("pause");
}
void loadMemberInfo(ifstream& inMemberFile, Member memberDetails[], int& numMembers) {
    inMemberFile.open("MemberInfo.dat", ios::in);
    if (!inMemberFile) {
        cout << "Error: Could not open file 'MemberInfo.dat'.\n";
        return;
    }
    numMembers = 0;
    while (inMemberFile >> memberDetails[numMembers].email >> memberDetails[numMembers].password
        >> memberDetails[numMembers].IDNumber >> memberDetails[numMembers].name
        >> memberDetails[numMembers].phone) {
        numMembers++;
    }
    inMemberFile.close();
}
int inputAnInteger(int begin, int end) {
    int input;
    cin >> input;
    if (input >= begin && input <= end)
        return input;
    else
        return -1;
}
void login(Member memberDetails[], int numMembers) {
    char email[40], password[24];
    int recordNumber;
    bool login = true;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;

    if (legal(email, password, memberDetails, numMembers, recordNumber)) {
        cout << "Login successful!\n\n";
        int choice;

        while (login)
        {
            cout << "Enter your choice:" << endl;
            cout << "1. Account Information\n";
            cout << "2. Buy Tickets\n";
            cout << "3. End\n? ";

            choice = inputAnInteger(1, 3);
            cout << endl;

            switch (choice)
            {
            case 1:
                accountInfor(memberDetails, numMembers, recordNumber); 
                break;

            case 2:
                login = false;
                break;

            case 3:
                login = false;
                break;

            default:
                cout << "Input Error!\n\n";
                break;
            }
        }
    }
    else {
        cout << "Invalid email or password.\n\n";
    }
}
bool legal(char email[], char password[], Member memberDetails[], int numMembers, int& recordNumber) {
    for (int i = 0; i < numMembers; i++) {
        if (strcmp(email, memberDetails[i].email) == 0 &&
            strcmp(password, memberDetails[i].password) == 0) {
            recordNumber = i;
            return true;
        }
    }
    return false;
}
void accountInfor(Member memberDetails[], int numMembers, int recordNumber) {
    bool info = true;
    cout << "Account Information:\n";
    cout << "1. Name: " << memberDetails[recordNumber].name << "\n";
    cout << "2. email: " << memberDetails[recordNumber].email << "\n";
    cout << "3. ID Number: " << memberDetails[recordNumber].IDNumber << "\n";
    cout << "4. Phone: " << memberDetails[recordNumber].phone << "\n";
    cout << "5. Password: " << memberDetails[recordNumber].password << "\n\n";
    int choice;
    char newValue[40];
    while (info) {
        cout << "which one you want to modify?(0- no modify) ";

        choice = inputAnInteger(0, 5);
        cout << endl;

        switch (choice)
        {
            case 0:
                info = false;
                break;
        case 1:
            cout << "enter correct data : ";
            cin >> newValue;
            strcpy_s(memberDetails[recordNumber].name, newValue);
            info = false;
            break;

        case 2:
            cout << "enter correct data : ";
            cin >> newValue;
            if (existingEmail(newValue, memberDetails, numMembers)) {
                cout << "Email already exists.\n\n";
                return;
            }
            strcpy_s(memberDetails[recordNumber].email, newValue); 
            info = false;
            break;

        case 3:
            cout << "enter correct data : ";
            cin >> newValue; 
            if (existingID(newValue, memberDetails, numMembers)) {
                cout << "ID Number already exists.\n\n";
                return;
            }
            strcpy_s(memberDetails[recordNumber].IDNumber, newValue);
            info = false;
            break;
        case 4:
            cout << "enter correct data : ";
            cin >> newValue; 
            strcpy_s(memberDetails[recordNumber].phone, newValue);
            info = false;
            break;
        case 5:
            cout << "enter correct data : ";
            cin >> newValue;
            strcpy_s(memberDetails[recordNumber].password, newValue);
            info = false;
            break;
        default:
            cout << "Input Error!\n\n";
            break;
        }
    }
    cout << "successful!!" << endl << endl; 
}
void newMember(Member memberDetails[], int& numMembers) {
    char newEmail[40], newIDNumber[12];

    cout << "Enter email: ";
    cin >> newEmail;
    if (existingEmail(newEmail, memberDetails, numMembers)) {
        cout << "Email already exists.\n\n";
        return;
    }

    cout << "Enter ID Number: ";
    cin >> newIDNumber;
    if (existingID(newIDNumber, memberDetails, numMembers)) {
        cout << "ID Number already exists.\n\n";
        return;
    }

    strcpy_s(memberDetails[numMembers].email, newEmail);
    strcpy_s(memberDetails[numMembers].IDNumber, newIDNumber);

    cout << "Enter password: ";
    cin >> memberDetails[numMembers].password;
    cout << "Enter name: ";
    cin >> memberDetails[numMembers].name;
    cout << "Enter phone: ";
    cin >> memberDetails[numMembers].phone;

    numMembers++;
    cout << "Member registered successfully!\n\n";
}
bool existingID(char newIDNumber[], Member memberDetails[], int& numMembers) {
    for (int i = 0; i < numMembers; i++) {
        if (strcmp(newIDNumber, memberDetails[i].IDNumber) == 0)
            return true;
    }
    return false;
}
bool existingEmail(char newEmail[], Member memberDetails[], int& numMembers) {
    for (int i = 0; i < numMembers; i++) {
        if (strcmp(newEmail, memberDetails[i].email) == 0)
            return true;
    }
    return false;
}
void saveMemberInfo(ofstream& outMemberFile, Member memberDetails[], int numMembers) {
    outMemberFile.open("MemberInfo.dat", ios::out);
    if (!outMemberFile) {
        cout << "Error: Could not open file 'MemberInfo.dat'.\n";
        return;
    }

    for (int i = 0; i < numMembers; i++) {
        outMemberFile << memberDetails[i].email << " "
            << memberDetails[i].password << " "
            << memberDetails[i].IDNumber << " "
            << memberDetails[i].name << " "
            << memberDetails[i].phone << "\n";
    }

    outMemberFile.close();
}