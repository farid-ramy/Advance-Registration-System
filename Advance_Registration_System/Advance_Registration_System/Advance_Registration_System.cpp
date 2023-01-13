#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

bool noData = false;

void SignUp() {
    system("CLS");
    cout << "+-----------------------------+" << endl;
    cout << "|                             |" << endl;
    cout << "|           Sign Up           |" << endl;
    cout << "|           _______           |" << endl;
    cout << "|                             |" << endl;
    cout << "|  Enter UserName & Password  |" << endl;
    cout << "|                             |" << endl;
    cout << "+-----------------------------+" << endl;

    while (true) {
        cout << "-> UserName :  ";
        string username;
        cin >> username;
        cout << "-> Password :  ";
        string password;
        cin >> password;

        bool found = false;
        ifstream myFile("file.txt");

        string USERNAME, PASSWORD;

        if (myFile.is_open()) {
            while (!myFile.eof()) {
                myFile >> USERNAME >> PASSWORD;
                if (username == USERNAME) {
                    found = true;
                    break;
                }
            }
            myFile.close();
        }

        if (found) {
            cout << endl << "< ERROR..UserName is Taken >" << endl << endl;
            continue;
        }
        else {
            fstream myFilee("file.txt", ios::app);
            myFilee << endl << username << " " << password;
            myFilee.close();
            cout << "< ADDED SUCCESSFULLY >" << endl;
            break;
        }
    }
}

void SignIn() {
    system("CLS");
    cout << "+-----------------------------+" << endl;
    cout << "|                             |" << endl;
    cout << "|           Sign In           |" << endl;
    cout << "|           _______           |" << endl;
    cout << "|                             |" << endl;
    cout << "|  Enter UserName & Password  |" << endl;
    cout << "|                             |" << endl;
    cout << "+-----------------------------+" << endl;

    while (true) {
        cout << "-> UserName :  ";
        string username;
        cin >> username;
        cout << "-> Password :  ";
        string password;
        cin >> password;

        bool found = false;
        ifstream myFile("file.txt");

        string USERNAME, PASSWORD;

        if (myFile.is_open()) {
            while (!myFile.eof()) {
                myFile >> USERNAME >> PASSWORD;
                if (username == USERNAME && password == PASSWORD) {
                    found = true;
                    break;
                }
            }
            myFile.close();
        }

        if (!found) {
            cout << endl << "< WRONG USERNAME OR PASSWORD >" << endl << endl;
            continue;
        }
        else {
            cout << endl << "< SIGN IN SUCCESSFULLY >" << endl << endl;
            break;
        }
    }
}

void Display() {
    system("CLS");

    ifstream myFile("file.txt");
    string USERNAME, PASSWORD;

    if (myFile.is_open()) {
        cout << setw(10) << "UserName" << setw(3) << " | Password" << endl;
        while (!myFile.eof()) {
            cout << "___________|____________" << endl;
            myFile >> USERNAME >> PASSWORD;
            cout << setw(10) << USERNAME << setw(3) << " | ";
            cout << PASSWORD[0];
            for (int i = 1; i < PASSWORD.length(); i++)
            {
                cout << "*";
            }
            cout << endl;
        }
        myFile.close();
    }
    else {
        cout << "<  NO DATA >" << endl << endl << endl;
        noData = true;
    }
}

void Delete() {
    Display();

    if (!noData) {
        cout << endl << endl << endl << "Enter the userName of the account you want to delete :  ";

        while (true) {
            string username;
            cin >> username;

            bool found = false;
            ifstream myFile("file.txt");

            string USERNAME, PASSWORD;

            while (!myFile.eof()) {
                myFile >> USERNAME >> PASSWORD;
                if (username == USERNAME) {
                    found = true;
                    break;
                }
            }
            myFile.close();

            if (!found) {
                cout << endl << "< ERROR..UserName isn't found >" << endl << " -> Please enter a valid username :  ";
                continue;
            }
            else {
                cout << "Enter the Password :  ";
                string password;
                cin >> password;
                while (password != PASSWORD) {
                    cout << endl << "< ERROR..Incorrect Password>" << endl << " -> Please enter again :  ";
                    cin >> password;
                }

                cout << "< DELETED SUCCESSFULLY >" << endl;


                ifstream myFile("file.txt");
                fstream temp("temp.txt", ios::app);

                while (!myFile.eof()) {
                    myFile >> USERNAME >> PASSWORD;
                    if(USERNAME != username)
                        temp << endl << USERNAME << " " << PASSWORD;
                }
                myFile.close();
                temp.close();

                remove("file.txt");
                rename("temp.txt","file.txt");

                break;
            }
        }

    }
}

void edit() {
    Display();

    if (!noData) {
        cout << endl << endl << endl << "Enter the userName of the account you want to edit :  ";

        while (true) {
            string username;
            cin >> username;

            bool found = false;
            ifstream myFile("file.txt");

            string USERNAME, PASSWORD;

            while (!myFile.eof()) {
                myFile >> USERNAME >> PASSWORD;
                if (username == USERNAME) {
                    found = true;
                    break;
                }
            }
            myFile.close();

            if (!found) {
                cout << endl << "< ERROR..UserName isn't found >" << endl << " -> Please enter a valid username :  ";
                continue;
            }
            else {
                cout << "Enter the Password :  ";
                string password;
                cin >> password;
                while (password != PASSWORD) {
                    cout << endl << "< ERROR..Incorrect Password>" << endl << " -> Please enter again :  ";
                    cin >> password;
                }

                string newChange;

                cout << "Do you want to change 1.UserName or 2.password : ";
                int choice;
                cin >> choice;
                while (choice != 1 && choice != 2) {
                    cout << "ERROR..INVALID CHOICE..Choose again: ";
                    cin >> choice;
                }

                if (choice == 1) { // username
                    while (true) {
                        cout << "Enter the new UserName : ";
                        cin >> newChange;

                        bool found = false;
                        ifstream myFile("file.txt");

                        string USERNAME, PASSWORD;

                        if (myFile.is_open()) {
                            while (!myFile.eof()) {
                                myFile >> USERNAME >> PASSWORD;
                                if (newChange == USERNAME) {
                                    found = true;
                                    break;
                                }
                            }
                            myFile.close();
                        }

                        if (found) {
                            cout << endl << "< ERROR..UserName is Taken >" << endl << endl;
                            continue;
                        }
                        else {
                            break;
                        }
                    }
                }
                else { //password
                    cout << "Enter the new Password : ";
                    cin >> newChange;
                }

                cout << "< DONE >" << endl;

                ifstream myFile("file.txt");
                fstream temp("temp.txt", ios::app);

                while (!myFile.eof()) {
                    myFile >> USERNAME >> PASSWORD;
                    if (USERNAME != username)
                        temp << endl << USERNAME << " " << PASSWORD;
                    else if(choice == 1)
                        temp << endl << newChange << " " << PASSWORD;
                    else
                        temp << endl << USERNAME << " " << newChange;
                }
                myFile.close();
                temp.close();

                remove("file.txt");
                rename("temp.txt", "file.txt");

                break;
            }
        }
    }
}

int main()
{
    cout << "+-----------------------------+" << endl;
    cout << "|                             |" << endl;
    cout << "|      1. Sign Up             |" << endl;
    cout << "|      2. Sign In             |" << endl;
    cout << "|      3. Display accounts    |" << endl;
    cout << "|      4. Delete account      |" << endl;
    cout << "|      5. Edit  account       |" << endl;
    cout << "|                             |" << endl;
    cout << "+-----------------------------+" << endl;
    int choice;
    cin >> choice;

    while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5) {
        cout << "ERROR..INVALID CHOICE..Choose again: ";
        cin >> choice;
    }

    if (choice == 1)
        SignUp();
    else if (choice == 2)
        SignIn();
    else if (choice == 3)
        Display();
    else if (choice == 4)
        Delete();
    else
        edit();
}
