#include "driver.cpp"
int main()
{
    LocationDetails locations;
    Stack cart;
    system("clear");
    string type;
    string username = login(type);
    if (type == "user")
    {
        int price = 0;
        cout << "Here user name is : " << username << endl;
        showTheBookList(cart, price);
        cart.displayCart();
        if (cart.sizeIs() != 0)
        {
            cout << RESET << endl;
            string location = locations.getDeliveryPrice(price);
            cout << location << endl;
            ofstream fout("delivery.txt", ios_base::out | ios_base::app);
            Stack cart2;
            while (cart.sizeIs())
            {
                Book b = cart.top();
                cart2.push(b);
                cart.pop();
            }
            fout << username << "\n"
                 << location << "\n"
                 << price << endl;
            fout.close();
            cart2.displayCart();
            while (cart2.sizeIs())
            {
                ofstream foout("delivery.txt", ios_base::out | ios_base::app);
                Book b = cart2.top();
                cart2.pop();
                foout << b.title << " " << b.author << " " << b.price << endl;
                foout.close();
            }
            ofstream ffout("delivery.txt", ios_base::out | ios_base::app);
            ffout << "--------------------------------------------------------" << endl;
            ffout.close();
            cout << WHITE << endl;
        }
    }
    else if (type == "admin")
    {
        string filename = "user_credentials.txt";
        LocationDetails l;

        // Initialize the library with existing user credentials
        Library library(filename);
        int choice;
        std::cout << "\033[1;33m";
        cout << "\nAdmin login successful. Welcome, " << username << "!\n";
        printSuccessfulLogin();

        bool adminExit = false;
        while (!adminExit)
        {
            printAdminMenu();
            cin >> choice;
            switch (choice)
            {
            case 1:
                viewAllUsers(library.getUserCredentials());
                break;
            case 2:
                adminMenu();
                break;
            case 3:
                l.areaInput();
                break;
            case 4:
                adminExit = true;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }
    return 0;
}