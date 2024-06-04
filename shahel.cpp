#include <iostream>
#include <fstream> // File
#include <string>
#include <unordered_map> // HashMap
#include <iomanip>       // For setw() -- setwidth (25)

using namespace std;

class Library
{
private:
    unordered_map<string, string> userCredentials; // Declaring Hash map
    string filename;

public:
    // Constructor
    Library(string filename) : filename(filename)
    {
        loadCredentials(); // Load existing user credentials from file
    }

    void registerUser(string username, string password)
    {
        if (userCredentials.find(username) == userCredentials.end()) // CHECK: USERNAME EXIST KORE NAKI NA
        {
            userCredentials[username] = password;
            std::cout << "\033[1;33m";
            cout << "\nUser registered successfully!\n";
            saveCredentials(); // Save updated user credentials to file
        }
        else
        {
            std::cout << "\033[1;33m";
            cout << "\nUsername already exists! Please choose a different username.\n";
        }
    }

    bool authenticateUser(string username, string password)
    {
        auto it = userCredentials.find(username); // auto: as 'it' will return an iterator type / we don't know the exact datatype
        if (it != userCredentials.end() && it->second == password)
        {
            return true;
        }
        return false;
    }

    const unordered_map<string, string> &getUserCredentials() const
    {
        return userCredentials;
    }

private:
    // This function ensures that when the program starts, it has the existing user credentials loaded into memory from the file, allowing for authentication and registration functionalities to work properly
    void loadCredentials()
    {
        ifstream file(filename);
        if (file.is_open())
        {
            string username, password;
            while (file >> username >> password) // Reading Username & password from file.
            {
                userCredentials[username] = password; // If username(key) already exists in the map, its corresponding value (password) is updated.
            }
            file.close();
        }
        else
        {
            cout << "----"; // cout << "Unable to open file. Creating a new file.\n";
        }
    }

    void saveCredentials()
    {
        ofstream file(filename);
        if (file.is_open())
        {
            for (const auto &pair : userCredentials)
            {
                file << pair.first << " " << pair.second << endl;
            }
            file.close();
        }
        else
        {
            cout << "Unable to open file for writing.\n";
        }
    }
};

void printHeader(const string &title)
{
    std::cout << "\033[31m";
    cout << "\n===========================================\n";
    cout << setw(25) << title << endl; // set width
    cout << "===========================================\n";
    std::cout << "\033[0m";
}

void printLibraryInteraction()
{
    std::cout << "\033[1;34m" // blue

              << R"(
       O
      /|\
      / \
    )" << "\033[0m"           // Reset color
              << "\033[1;32m" // green
              << R"(
       __
      /    \
     | BOOK |
      \____/
    )" << "\033[0m"           // Reset color
              << "\033[1;31m" // red
              << R"(
          O
         /|\
         / \
    )" << "\033[0m";          // Reset color
}

void printSuccessfulLogin()
{
    std::cout << "\033[1;32m"; // green
    std::cout << R"(
          O
         \|/
          |
         / \
    )";
    std::cout << "\033[0m"; // Reset color

    std::cout << "\033[1;34m"; // blue
    std::cout << R"(
      *     *
         *
  *     *     *
         *
      *     *
    )";
    std::cout << "\033[0m"; // Reset color

    std::cout << "\033[0m"; // Reset color
}

void printFailedLogin()
{
    std::cout << "\033[1;31m"; // red
    std::cout << R"(
        ___
       /     \
      |       |
      |  O O  |
      |   ^   |
      |  '-'  |
       \_____/
    )";
    std::cout << "\033[0m"; // Reset color

    std::cout << "\033[1;33m"; // yellow
    std::cout << "\nLogin Failed. Please try again.\n";
    std::cout << "\033[0m"; // Reset color
}

bool authenticateAdmin(string username, string password)
{
    return (username == "ADMIN" && password == "ADMIN");
}

void printAdminMenu()
{
    printHeader("Admin Menu");
    cout << "Choose an option:\n";
    cout << "1. View All Users\n";
    cout << "2. Delivey Page \n";
    cout << "3. Modify Delivery Locations : " << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

void viewAllUsers(const unordered_map<string, string> &userCredentials)
{
    printHeader("All Registered Users");
    for (const auto &pair : userCredentials)
    {
        cout << "Username: " << pair.first << endl;
    }
    cout << "Press any key to return to the main menu...";
    cin.ignore();
    cin.get();
}

string login(string &type)
{
    system("clear") ; 
    string filename = "user_credentials.txt";

    // Initialize the library with existing user credentials
    Library library(filename);

    std::cout << "\033[1;33m";
    cout << "Welcome to the Library Management System!\n";
    std::cout << "\033[0m"; // Reset color

    int choice;
    string username, password;
    bool exit = false; // Control variable to exit the loop

    while (!exit)
    {
        system("clear") ; 
        printLibraryInteraction();
        printHeader("Main Menu");
        cout << "Choose an option:\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Admin Login\n";
        cout << "Enter your choice (or any other key to exit): ";
        cin >> choice;

        switch (choice)
        {
        case 1: // Login
            printHeader("Login");
            cout << "Please log in.\n";
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            if (library.authenticateUser(username, password))
            {
                type = "user";
                std::cout << "\033[1;33m";
                cout << "\nLogin successful. Welcome, " << username << "!\n";
                printSuccessfulLogin();
                exit = true; // Set exit to true to exit the loop
            }
            else
            {
                std::cout << "\033[1;33m";
                cout << "\nInvalid username or password. Please try again.\n";
                printFailedLogin();
            }
            break;

        case 2: // Registration
            printHeader("Registration");
            cout << "Please register.\n";
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            type = "user";
            library.registerUser(username, password);
            break;
        case 3: // Admin Login
            printHeader("Admin Login");
            cout << "Please log in as admin.\n";
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            if (authenticateAdmin(username, password))
            {
                cout << "Admin login successfull" << endl;
                type = "admin";
                exit = true;
                break;
            }
            else
            {
                std::cout << "\033[1;33m";
                cout << "\nInvalid admin credentials. Please try again.\n";
                printFailedLogin();
            }
            break;

        default:
            std::cout << "\033[1;33m";
            cout << "\nThank you for using the Library Management System. Goodbye!\n";
            exit = true; // Set exit to true to exit the loop
            break;
        }
    }

    return username;
}