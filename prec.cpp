#include <iostream>
#include <fstream>
#include <iomanip>
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#define RESET_BG "\033[0m"
#define BLACK_BG "\033[40m"
#define RED_BG "\033[41m"
#define GREEN_BG "\033[42m"
#define YELLOW_BG "\033[43m"
#define BLUE_BG "\033[44m"
#define MAGENTA_BG "\033[45m"
#define CYAN_BG "\033[46m"
#define WHITE_BG "\033[47m"
#define DEFAULT_BG "\033[49m"
using namespace std;

#define location_size 3

struct Location
{
    string district;
    string location_name;
    string distance;
    Location *left;
    Location *right;
    Location() {}
    Location(string location, string distance) : location_name(location), distance(distance) {}
};

class LocationTree
{

private:
    Location *mainroot;
    Location *left;
    Location *right;
    string defaultLocation;
    string district;
    int defaultDistance;
    int startingprice;
    int size;
    int index = 0;
    bool found = false;

    void insert(Location *&root, Location *node)
    {
        if (!root)
        {
            root = node;
        }
        else if (stoi(root->distance) >= stoi(node->distance))
        {
            // cout<<"inserting left "<<endl;
            // cout<<"root left : "<<node->location_name<<endl;
            insert(root->left, node);
        }
        else
        {
            // cout<<"inserting right"<<endl;
            insert(root->right, node);
        }
    }

public:
    LocationTree(Location *rt, string dis, int starting)
    {
        district = dis;
        mainroot = rt;
        defaultLocation = rt->location_name;
        startingprice = starting;
        size = 0;
    }

    bool find(Location *root, string locationname)
    {
        if (root == nullptr)
        {
            return false;
        }
        else if (root->location_name == locationname)
        {
            return true;
        }
        else
        {
            return find(root->left, locationname) || find(root->right, locationname);
        }
    }

    bool find(string locationname)
    {
        return find(mainroot, locationname);
    }

    Location *findRightAncestor(Location *root)
    {
        if (root->left->left == nullptr)
        {
            root->left = root->left->right;
            return root->left;
        }
        else
        {
            return findRightAncestor(root->left);
        }
    }

    Location *deleteArea(Location *root, string locationname)
    {
        if (root == NULL)
            return root;
        else if (root->location_name == locationname)
        {
            found = true;
            size-- ; 
            if (root->left == NULL)
            {
                Location *temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == NULL)
            {
                Location *temp = root->left;
                delete root;
                return temp;
            }

            Location *Parent = root;
            Location *succ = root->right;
            while (succ->left != NULL)
            {
                Parent = succ;
                succ = succ->left;
            }

            root->location_name = succ->location_name;

            if (Parent->left == succ)
                Parent->left = succ->right;
            else
                Parent->right = succ->right;

            delete succ;
            return root;
        }
        else
        {
            if (!found)
                root->left = deleteArea(root->left, locationname);
            if (!found)
                root->right = deleteArea(root->right, locationname);
            return root;
        }
    }

    void deleteArea(string locationname)
    {
        found = false;
        mainroot = deleteArea(mainroot, locationname);
    }

    void InsertItem(Location *node)
    {
        // cout<<node->location_name<<endl;
        // cout<<node->distance<<endl;
        if (node->location_name == defaultLocation)
            return;
        insert(mainroot, node);
        ++size;
    }

    int getStaringPrice()
    {
        return startingprice;
    }

    void reset()
    {
        index = 0;
    }

    int getSize()
    {
        return size + 1;
    }
    string **getList()
    {
        reset();
        string **lst = new string *[getSize()];
        for (int i = 0; i < getSize(); ++i)
        {
            lst[i] = new string[2];
        }
        print(mainroot, lst);
        // cout<<"it is done"<<endl;
        return lst;
    }

    void print(Location *root, string **lst)
    {
        if (root != nullptr)
        {
            print(root->left, lst);
            lst[index][0] = root->location_name;
            lst[index][1] = root->distance;
            index++;
            // cout<<root->location_name<<endl;
            print(root->right, lst);
        }
    }
    void inorder()
    {
        inorderTraverseal(mainroot);
    }

    void inorderTraverseal(Location *root)
    {
        if (root != nullptr)
        {
            inorderTraverseal(root->left);
            if (root->location_name != defaultLocation)
                cout << root->location_name << " ";
            inorderTraverseal(root->right);
        }
    }

    void putIntoFile()
    {
        putPreorderIntofile(mainroot);
    }

    void putPreorderIntofile(Location *node)
    {
        if (node != nullptr)
        {
            // cout<<"here writting "<<endl;
            ofstream fout("hello.txt", ios_base::out | ios_base::app);
            fout << "(" << district << ")(" << node->location_name << ")(" << node->distance << ")" << endl;
            fout.close();
            putPreorderIntofile(node->left);
            putPreorderIntofile(node->right);
        }
    }

    void PrintDistrict()
    {
        inorderTraverseal(mainroot);
    }
};

class LocationDetails
{
private:
    LocationTree *location[location_size] = {
        new LocationTree(new Location("Jamuna_Future_Park", "10"), "Dhaka", 10),
        new LocationTree(new Location("patiya", "10"), "Chattogram", 20),
        new LocationTree(new Location("Badhra", "20"), "Rajshahi", 30)};
    string locations[3] = {"Dhaka", "Chattogram", "Rajshahi"};
    void fillUp()
    {
        ifstream fin("hello.txt", ios_base::in);
        string line;
        int index = 0;
        while (getline(fin, line))
        {
            string str[3];
            string s;
            for (int i = 0; i < line.length(); ++i)
            {
                if (line[i] == '(')
                {
                    s = "";
                }
                else if (line[i] == ')')
                {
                    str[index] = s;
                    index = (index + 1) % 3;
                }
                else
                {
                    s += line[i];
                }
            }
            for (int x = 0; x < location_size; ++x)
                if (str[0] == locations[x])
                {
                    location[x]->InsertItem(new Location(str[1], str[2]));
                }
        }
    }

public:
    LocationDetails()
    {
        fillUp();
    }

    void areaInput()
    {
        while (true)
        {
            system("clear");
            cout << "\tChoose from below :" << endl;
            cout << "\t1. Add New Area : " << endl;
            cout << "\t2. Delete an Area : " << endl;
            cout << "\t3. Go Back" << endl;
            cout << "Choose -> ";
            bool complete = false;
            int choose;
            cin >> choose;
            switch (choose)
            {
            case 1:
            {
                system("clear");
                takeAreaInput();
                system("pause");
                break;
            }
            case 2:
            {
                system("clear");
                deleteArea();
                system("pause");
                break;
            }
            case 3:
            {
                complete = true;
                break;
            }
            default:
            {
                cout << "\n\t--------- Invalid Input ---------" << endl;
                break;
            }
            }
            if (complete)
                return;
        }
    }

    void deleteArea()
    {
        system("clear");
        cout << "\t\t\t\t\t\t\t\tChoose District" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Enter -1 to go back : " << endl;
        for (int i = 0; i < location_size; ++i)
        {
            cout << i + 1 << " ) " << locations[i] << "\t\t\t";
        }
        cout << endl;
        cout << endl;
        int x;
        cout << "Choose District : ";
        cin >> x;
        cout << endl;
        string **lst = location[x - 1]->getList();
        int size = location[x - 1]->getSize();
        cout << "\t\t\t\t\t\t\tCurrent Areas" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl
             << endl;
        for (int i = 0; i < size; ++i)
        {
            cout << i << " ) " << "Area : " << lst[i][0] << endl
                 << endl;
        }
        if (x == -1)
            return;
        deleteArea(x - 1, size, lst);
    }

    void deleteArea(int x, int size, string **lst)
    {
        while (true)
        {
            cout << "Enter -1 to go back : " << endl;
            cout << "Choose area to delete : " << endl;
            int y;
            cin >> y;
            if (y >= size)
            {
                cout << "Invalid input : ";
            }
            else if (y == -1)
            {
                return;
            }
            else
            {
                cout << "Deleting Area is :" << lst[y][0] << endl;
                location[x]->deleteArea(lst[y][0]);
                cout << "Successfully Removed." << endl;
                lst = location[x]->getList();
                size = location[x]->getSize();
                cout<<"size is : "<<size<<endl;
                cout << "\t\t\t\t\t\t\tCurrent Areas" << endl;
                cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl
                     << endl;
                for (int i = 0; i < size; ++i)
                {
                    cout << i << " ) " << "Area : " << lst[i][0] << endl
                         << endl;
                }
                location[x]->inorder();
                cout << endl;
                ofstream fout("hello.txt");
                fout.close();
                for (int i = 0; i < location_size; ++i)
                {
                    location[i]->putIntoFile();
                }
            }
        }
    }
    void takeAreaInput()
    {
        system("clear");
        cout << "\t\t\t\t\t\t\t\tChoose District" << endl;
        cout << "Enter -1 to go back : " << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl
             << endl;
        for (int i = 0; i < 4; ++i)
        {
            cout << i + 1 << " ) " << locations[i] << "\t\t\t";
        }
        cout << endl;
        cout << endl;
        int x;
        cout << "Choose District : ";
        cin >> x;
        cout << endl;
        string **lst = location[x - 1]->getList();
        int size = location[x - 1]->getSize();
        cout << "\t\t\t\t\t\t\tCurrent Areas" << endl;
        cout << "------------------------------------------------------------------------------------------------------------------------------------" << endl
             << endl;
        for (int i = 0; i < size; ++i)
        {
            cout << i << " ) " << "Area : " << lst[i][0] << endl
                 << endl;
        }
        if (x == -1)
            return;
        takeAreaInput(x - 1);
    }

    void takeAreaInput(int x)
    {
        string quit;
        while (true)
        {
            if (quit == "q")
                break;
            string locationname;
            string district;
            string distance;
            cout << "Enter Area name : ";
            cin >> locationname;
            cout << "Enter distance from Z point : ";
            cin >> distance;
            if (!location[x]->find(locationname))
                location[x]->InsertItem(new Location(locationname, distance));
            else
                cout << "The Area is already exist in the list." << endl;
            cout << "Enter \"y\" to input more or \"q\" to leave the page : ";
            cin >> quit;
        }
        location[x]->inorder();
        cout << endl;
        ofstream fout("hello.txt");
        fout.close();
        for (int i = 0; i < location_size; ++i)
        {
            location[i]->putIntoFile();
        }
    }

    string getDeliveryPrice(int &price)
    {
        system("clear");
        cout << BLUE << YELLOW_BG << "####################################################################################################################################" << endl;
        cout << "#                                                                                                                                  #" << endl;
        cout << "#                                                          " << YELLOW << RED_BG << " Choose District" << BLUE << YELLOW_BG << "                                                        " << "#" << endl;
        cout << "#                                                                                                                                  #" << endl;
        cout << "####################################################################################################################################" << endl;
        for (int i = 0; i < location_size; ++i)
        {
            cout << YELLOW << CYAN_BG;
            cout << left << i + 1 << " ) " << setw(260) << left << locations[i] << endl;
            cout << RESET << RESET_BG;
        }
        cout << "                                                       " << endl;
        cout << flush;
        cout << endl;
        cout << "Choose District : ";
        int x;
        cout << "\b";
        cin >> x;
        cout << endl;
        string **lst = location[x - 1]->getList();
        int size = location[x - 1]->getSize();
        cout << BLUE << YELLOW_BG << "####################################################################################################################################" << endl;
        cout << "#                                                                                                                                  #" << endl;
        cout << "#                                                          " << YELLOW << RED_BG << " Choose Area" << BLUE << YELLOW_BG << "                                                            " << "#" << endl;
        cout << "#                                                                                                                                  #" << endl;
        cout << "####################################################################################################################################" << endl;
        cout << YELLOW << CYAN_BG;
        for (int i = 0; i < size; ++i)
        {
            cout << GREEN << i << " ) " << YELLOW << "Area : " << WHITE << setw(55) << left << lst[i][0] << YELLOW << "Delivery charge : " << WHITE << setw(48) << left << location[x - 1]->getStaringPrice() + (stoi(lst[i][1])) * 2 << endl;
        }
        cout << RESET << RESET_BG << endl;
        cout << "Enter your selection : ";
        cin >> size;
        cout << endl;
        cout << BLUE << YELLOW_BG << "####################################################################################################################################" << endl;
        cout << "#                                                                                                                                  #" << endl;
        cout << "#                                                          " << YELLOW << RED_BG << "Delivery Location" << BLUE << YELLOW_BG << "                                                       " << "#" << endl;
        cout << "#                                                                                                                                  #" << endl;
        cout << "####################################################################################################################################" << endl;
        cout << GREEN_BG;
        cout << "Your Selected Delivery Location is : " << setw(95) << lst[size][0] << endl
             << endl;
        cout << "Books price : " << price << endl;
        cout << "Delivery Charge : " << location[x - 1]->getStaringPrice() + (stoi(lst[size][1])) * 2 << endl;
        price += location[x - 1]->getStaringPrice() + (stoi(lst[size][1])) * 2;
        cout << "Total : " << price << endl
             << endl;
        cout << RESET << endl;
        return lst[size][0] + "," + locations[x - 1];
    }
};