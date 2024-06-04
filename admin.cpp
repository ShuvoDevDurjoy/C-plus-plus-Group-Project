#include <iostream>
#include "queuelinked.cpp"
#include <fstream>
#include <string>
// #include <windows.h>
// #include <conio.h>
using namespace std;
const string fileName = "delivery.txt";

// void SetConsoleColors(WORD textColor, WORD bgColor)
// {
//     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//     // Combine the text and background color
//     SetConsoleTextAttribute(hConsole, textColor | bgColor);
// }

class delivery
{
private:
    string name;
    string address;
    string money_amount;

public:
    string booklist[10];
    delivery()
    {
        name = " ";
        address = " ";
        money_amount = "0.0";
        for (int i = 0; i < 10; i++)
        {
            booklist[i] = "Empty";
        }
    }

    delivery(string Name, string Address, string Money_amount)
    {
        name = Name;
        address = Address;
        money_amount = Money_amount;
        for (int i = 0; i < 10; i++)
        {
            booklist[i] = "Empty";
        }
    }

    string getName()
    {
        return name;
    }

    string getAddress()
    {
        return address;
    }

    string getMoneyAmount()
    {
        return money_amount;
    }

    void setName(string Name)
    {
        name = Name;
    }

    void setAddress(string Address)
    {
        address = Address;
    }
};

void readfromFile(QueueLinked<delivery> &queuelist)
{
    ifstream readFile;
    string line;
again:
    readFile.open(fileName);

    if (!readFile)
    {
        cout << "File could not be opened!" << endl;
        ofstream writeFile(fileName);
        writeFile.close();
        cout << "File created successfully" << endl;
        goto again;
    }
    while (getline(readFile, line))
    {
        if (line == " ")
        {
            break;
        }
        string Name = line;
        string Address;
        string Amount;

        getline(readFile, Address);
        getline(readFile, Amount);
        delivery del(Name, Address, Amount);
        int a = 0;
        while (getline(readFile, line))
        {
            if (line == "--------------------------------------------------------")
            {
                break;
            }
            del.booklist[a] = line;
            a++;
        }
        queuelist.Enqueue(del);
    }

    readFile.close();

    // cout << "Data read from the file successfully." << endl;
}

void addToFile(delivery del)
{
    ofstream appendFile;
    appendFile.open(fileName, ios::app);

    if (!appendFile)
    {
        cout << "File could not be opened!" << endl;
        return;
    }

    appendFile << del.getName() << endl;
    appendFile << del.getAddress() << endl;
    appendFile << del.getMoneyAmount() << endl;
    string book;
    for (int i = 0; i < 10; i++)
    {
        string book = del.booklist[i];
        if (book == "Empty")
        {
            break;
        }
        else
        {
            appendFile << book << endl;
        }
    }
    appendFile << "--------------------------------------------------------" << endl;

    appendFile.close();

    // cout << "Data written to the file successfully." << endl;
}

void printDeliveries()
{
    QueueLinked<delivery> deliveries;
    readfromFile(deliveries);
    cout << "\tPending Deliveries :\n"
         << endl;
    while (!deliveries.IsEmpty())
    {
        delivery del;
        deliveries.Dequeue(del);
        if (del.getName() == " ")
        {
            cout << "\n\t--------- No Deliveries ---------" << endl;
        }
        else
        {
            cout << endl;
            cout << "Name: " << del.getName() << endl;
            cout << "Address: " << del.getAddress() << endl;
            cout << "Money Amount: " << del.getMoneyAmount() << endl;
            cout << "Book List:" << endl;
            for (int i = 0; i < 10; i++)
            {
                string book = del.booklist[i];
                if (book == "Empty")
                {
                    break;
                }
                cout << (i + 1) << ". " << book << endl;
            }
            cout << endl;
        }
    }

    char c;
    cin >> c;
}

void clearAllDeliveries()
{
    ofstream writeFile;
    writeFile.open(fileName);
    if (!writeFile)
    {
        cout << "File could not be opened!" << endl;
        return;
    }
    writeFile << "";
    writeFile.close();
}

void writeToFile(QueueLinked<delivery> &deliveries)
{
    ofstream writeFile;
    writeFile.open(fileName);

    if (!writeFile)
    {
        cout << "File could not be opened!" << endl;
        return;
    }

    while (!deliveries.IsEmpty())
    {
        delivery del;
        deliveries.Dequeue(del);
        writeFile << del.getName() << endl;
        writeFile << del.getAddress() << endl;
        writeFile << del.getMoneyAmount() << endl;
        string book;
        for (int i = 0; i < 10; i++)
        {
            string book = del.booklist[i];
            if (book == "Empty")
            {
                break;
            }
            else
            {
                writeFile << book << endl;
            }
        }
        writeFile << "--------------------------------------------------------" << endl;
    }

    writeFile.close();

    // cout << "Data written to the file successfully." << endl;
}

void completeDelivery()
{
    system("clear");
    QueueLinked<delivery> deliveryqueue;
    readfromFile(deliveryqueue);
    delivery del;
    deliveryqueue.Dequeue(del);
    if (del.getName() == " ")
    {
        cout << "\n\t--------- No Deliveries ---------" << endl;
    }
    else
    {
        // cout<<"\nDequeued : \n";
        // cout<<del.getName()<<endl;
        // cout<<del.getAddress()<<endl;
        // cout<<del.getMoneyAmount()<<endl;
        writeToFile(deliveryqueue);
        cout << "\n\t--------- First Delivery Completed ---------" << endl;
        char c ; 
        getchar() ; 
        getchar() ; 
    }
}

void adminMenu()
{
    while (true)
    {
        system("clear");
        cout << "\tChoose from below :" << endl;
        cout << "\t1. View Delivery List" << endl;
        cout << "\t2. Complete the latest delivery" << endl;
        cout << "\t3. Clear Delivery List" << endl;
        cout << "\t4. Go Back" << endl;
        cout << "Choose -> ";
        bool shesh = false;
        int choose;
        cin >> choose;
        switch (choose)
        {
        case 1:
        {
            system("clear");
            printDeliveries();
            system("pause");
            break;
        }
        case 2:
        {
            completeDelivery();
            system("pause");
            break;
        }
        case 3:
        {
            system("clear");
            clearAllDeliveries();
            cout << "\n\t--------- All Deliveries Cleared ---------" << endl;
            system("pause");
            break;
        }
        case 4:
        {
            shesh = true;
            break;
        }
        default:
        {
            cout << "\n\t--------- Invalid Input ---------" << endl;
            break;
        }
        }

        if (shesh)
        {
            break;
        }
    }
}
