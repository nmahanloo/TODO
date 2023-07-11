// NimaMahanloo_Inventory_Inquisitor.cpp
// Nima Mahanloo - CISP 400
// 03/09/2018
#include <iostream>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <sstream>
#include <string>
#include <fstream>
#include <stdio.h>
using namespace std;
// A structure for fstream
struct itemStruct
{
    string iName, iDesc, tChar;
    int iQuantity;
    double iPrice;
    double iWhole;
};
// An integer function to get item quantity from user in
int getQuantity(char select)
{
    char* quantityChar;
    int quantity, rate, counter, rateCounter;
    bool authorized = false;
    while (authorized == false)
    {
        quantityChar = (char*)malloc(sizeof(char));
        quantity = 0;
        rate = 1;
        authorized = true;
        if (select == 'q')
        {
            cout << "Please enter item quantity > ";
        }
        else
        {
            cout << "Please enter item number > ";
        }
        cin >> quantityChar;
        counter = 0;
        while (quantityChar[counter] != '\0')
        {
            if (isdigit(quantityChar[counter]) == false)
            {
            authorized = false;
            }
            counter++;
        }
    }
    for (rateCounter = 1; rateCounter < counter; rateCounter++)
    {
        rate *= 10;
    }
    counter = 0;
    while (quantityChar[counter] != '\0')
    {
        quantity += (int(quantityChar[counter])-48)*rate;
        rate /= 10;
        counter++;
    }
    return quantity;
}
// A double function to get item price from user in
double getPrice()
{
    int counter, rateCounter, floatIndex, rate, dotChar;
    double price, floatPrice;
    bool authorized = false;
    char* priceChar;
    while (authorized == false)
    {
        authorized = true;
        counter = 0;
        dotChar = 0;
        priceChar = (char*)malloc(sizeof(char));
        cout << "Please enter item price > ";
        cin >> priceChar;
        while (priceChar[counter] != '\0')
        {
            if (priceChar[counter] == '.')
            {
                dotChar++;
            }
            if (((isdigit(priceChar[counter]) == false) && (priceChar[counter] != '.')) || (dotChar > 1))
            {
                authorized = false;
            }
            counter++;
        }
    }
    if (dotChar == 1)
    {
        rateCounter = 0;
        while (priceChar[rateCounter] != '.')
        {
            rateCounter++;
        }
        rate = 1;
        for (counter = 1; counter < rateCounter; counter++)
        {
            rate *= 10;
        }
        counter = 0;
        while (priceChar[counter] != '.')
        {
            price += (int(priceChar[counter])-48)*rate;
            rate /= 10;
            counter++;
        }
        counter = rateCounter+1;
        floatIndex = counter;
        rateCounter = 0;
        while (priceChar[counter] != '\0')
        {
            rateCounter++;
            counter++;
        }
        rate = 1;
        for (counter = 1; counter < rateCounter; counter++)
        {
            rate *= 10;
        }
        floatPrice = 0;
        counter = floatIndex;
        rateCounter = 0;
        while (priceChar[counter] != '\0')
        {
            floatPrice += (int(priceChar[counter])-48)*rate;
            rate /= 10;
            counter++;
            rateCounter ++;
        }
        rate = 1;
        for (counter = 0; counter < rateCounter; counter++)
        {
            rate *= 10;
        }
        floatPrice /= rate;
        price += floatPrice;
    }
    else if (dotChar == 0)
    {
        rateCounter = 0;
        rate = 1;
        while (priceChar[rateCounter] != '\0')
        {
            rateCounter++;
        }
        rate = 1;
        for (counter = 1; counter < rateCounter; counter++)
        {
            rate *= 10;
        }
        counter = 0;
        while (priceChar[counter] != '.')
        {
            price += (int(priceChar[counter])-48)*rate;
            rate /= 10;
            counter++;
        }
    }
    return price;
}
// A character function to get user input for selected item for edit
char getEditChoice()
{
    char editChoice = '?';
    while ((editChoice != 'n') && (editChoice != 'd') && (editChoice != 'q') && (editChoice != 'p') && (editChoice != 'a'))
    {
        cout << "Edit item name <n>" << endl << "Edit item description <d>" <<
        endl << "Edit item quantity <q>" << endl << "Edit item price <p>" <<
        endl << "Edit all <a>" << endl << "> ";
        cin >> editChoice;
    }
    cout << endl;
    return editChoice;
}
// A character function to get user input about item search
char getSearchChoice()
{
    char searchChoice = '?';
    while ((searchChoice != 'n') && (searchChoice != 'a') && (searchChoice != 'd') && (searchChoice != 'q') && (searchChoice != 'p') && (searchChoice != 'w') && (searchChoice != 't'))
    {
        cout << "Search by item number <n>" << endl << "Search by item name <a>" <<
        endl << "Search by item description <d>" << endl << "Search by item Quantity <q>" <<
        endl << "Search by item price <p>" << endl << "Search by item whole price <w>" <<
        endl << endl << "> ";
        cin >> searchChoice;
    }
    cout << endl;
    return searchChoice;
}
// Program main class
class Inventory
{
    public:
        friend void readFile(Inventory*&);
        friend void writeFile(Inventory*);
        Inventory();
        virtual ~Inventory();
        char mainMenu();
        void addNode(Inventory*&);
        void addItem(char);
        void addItem(itemStruct);
        void setItemNo(int);
        void setFirstItem(bool);
        void editItem(Inventory*&, int, char);
        void deleteItem(Inventory*&, Inventory*&, int);
        void searchItem(Inventory*, string, int&, int*&);
        bool searchItem(Inventory*, int);
        void searchItem(Inventory*, double, int&, int*&);
        void searchItem2(Inventory*, string, int&, int*&);
        void searchItem2(Inventory*, int, int&, int*&);
        void searchItem2(Inventory*, double, int&, int*&);
        void displayList(Inventory*);
        void deleteList(Inventory*&);
    private:
        Inventory* next;
        Inventory* prev;
        string itemName;
        string itemDesc;
        int itemQuantity;
        double itemPrice;
        double wholePrice;
        bool firstItem;
        time_t itemTime;
        string timeChar;
        int itemNo;
};
// Default constructor
Inventory::Inventory()
{
    next = nullptr;
    prev = nullptr;
    itemQuantity = 0;
    itemPrice = 0.0;
    wholePrice = 0.0;
    firstItem = false;
    itemNo = 0;
}
// Virtual destructor
Inventory::~Inventory()
{
    // This is a doubly linked list
}
// a module to access and assign the class private member
void Inventory::setItemNo(int num)
{
    itemNo = num;
}
// A module to add a Node to linked list
void Inventory::addNode(Inventory* (&last))
{
    if (firstItem == false)
    {
        last->next = new Inventory;
        last->next->prev = last;
        last = last->next;
        last->itemNo = last->prev->itemNo + 1;
    }
}
// A module to access and set a private member as first node
void Inventory::setFirstItem(bool firstItem)
{
    this->firstItem = firstItem;
}
// A module to add item to inventory list
void Inventory::addItem(char addType)
{
    cin.ignore(1);
    if ((addType == 'n') || (addType == 'a'))
    {
        cout << "Please Enter Item Name > ";
        getline(cin, itemName);
    }
    if ((addType == 'd') || (addType == 'a'))
    {
        cout << "Please Enter Item Description > ";
        getline(cin, itemDesc);
    }
    if ((addType == 'q') || (addType == 'a'))
    {
        itemQuantity = getQuantity('q');
    }
    if ((addType == 'p') || (addType == 'a'))
    {
        itemPrice = getPrice();
    }
    wholePrice = itemQuantity * itemPrice;
    itemTime = time(0);
    timeChar = ctime(&itemTime);
    if (firstItem == true)
    {
        firstItem = false;
    }
    cout << endl;
}
// A module to add load item from file to inventory list
void Inventory::addItem(itemStruct item)
{
    itemName = item.iName;
    itemDesc = item.iDesc;
    itemQuantity = item.iQuantity;
    itemPrice = item.iPrice;
    wholePrice = item.iWhole;
    timeChar = item.tChar;
    if (firstItem == true)
    {
        firstItem = false;
    }
}
// A module to delete an item from inventory list
void Inventory::deleteItem(Inventory* (&first), Inventory* (&last), int itemNum)
{
    Inventory* curr = first;
    Inventory* temp = nullptr;
    bool deleteNode = false;
    while ((curr != nullptr) && (deleteNode == false))
    {
        if (curr->itemNo == itemNum)
        {
            deleteNode = true;
        }
        else
        {
            curr = curr->next;
        }
    }
    if (curr->prev == nullptr)
    {
        temp = curr;
        curr = curr->next;
        first = curr;
        curr->prev = nullptr;
        delete temp;
        temp = nullptr;
        while (curr != nullptr)
        {
            curr->itemNo -= 1;
            curr = curr->next;
        }
    }
    else if (curr->next == nullptr)
    {
        temp = curr;
        curr = curr->prev;
        last = curr;
        curr->next = nullptr;
        delete temp;
        temp = nullptr;
    }
    else if (curr == nullptr){}
    else
    {
        temp = curr;
        curr = curr->prev;
        curr->next = curr->next->next;
        curr->next->prev = curr;
        delete temp;
        temp = nullptr;
        curr = curr->next;
        while (curr != nullptr)
        {
            curr->itemNo--;
            curr = curr->next;
        }
    }
}
// A module to search items in list by name
void Inventory::searchItem(Inventory* first, string searchName, int &findCount, int* (&findNum))
{
    bool findFlag = false;
    Inventory* curr = first;
    while (curr != nullptr)
    {
        if (curr->itemName == searchName)
        {
            cout << curr->itemNo << ". " << curr->itemName << endl
            << setw(3) << " " << curr->itemDesc << endl << setw(3) << " " << "Quantity : " << curr->itemQuantity
            << endl << setw(3) << " " << "Price : $" << curr->itemPrice << endl << setw(3) << " " << "WholePrice : $" << curr->wholePrice
            << endl <<  setw(3) << " " << "Add Time : " << curr->timeChar << endl << endl;
            findFlag = true;
            findNum[findCount] = curr->itemNo;
            findCount++;
        }
        curr = curr->next;
    }
    if (findFlag == false)
    {
        cout << "Item not found!" << endl << endl;
    }
}
// A boolean function to search items in list by item number
bool Inventory::searchItem(Inventory* first, int searchNum)
{
    bool findFlag = false;
    Inventory* curr = first;
    while (curr != nullptr)
    {
        if (curr->itemNo == searchNum)
        {
            cout << curr->itemNo << ". " << curr->itemName << endl
            << setw(3) << " " << curr->itemDesc << endl << setw(3) << " " << "Quantity : " << curr->itemQuantity
            << endl << setw(3) << " " << "Price : $" << curr->itemPrice << endl << setw(3) << " " << "WholePrice : $" << curr->wholePrice
            << endl <<  setw(3) << " " << "Add Time : " << curr->timeChar << endl << endl;
            findFlag = true;
        }
        curr = curr->next;
    }
    if (findFlag == false)
    {
        cout << "Item not found!" << endl << endl;
    }
    return findFlag;
}
// A module to search items in list by price
void Inventory::searchItem(Inventory* first, double searchPrice, int &findCount, int* (&findNum))
{
    bool findFlag = false;
    Inventory* curr = first;
    while (curr != nullptr)
    {
        if ((fabs(curr->itemPrice - searchPrice)) < 0.01)
        {
            cout << curr->itemNo << ". " << curr->itemName << endl
            << setw(3) << " " << curr->itemDesc << endl << setw(3) << " " << "Quantity : " << curr->itemQuantity
            << endl << setw(3) << " " << "Price : $" << curr->itemPrice << endl << setw(3) << " " << "WholePrice : $" << curr->wholePrice
            << endl <<  setw(3) << " " << "Add Time : " << curr->timeChar << endl << endl;
            findFlag = true;
            findNum[findCount] = curr->itemNo;
            findCount++;
        }
        curr = curr->next;
    }
    if (findFlag == false)
    {
        cout << "Item not found!" << endl << endl;
    }
}
// A module to search items in list by description
void Inventory::searchItem2(Inventory* first, string searchDesc, int &findCount, int* (&findNum))
{
    bool findFlag = false;
    Inventory* curr = first;
    while (curr != nullptr)
    {
        if (curr->itemDesc == searchDesc)
        {
            cout << curr->itemNo << ". " << curr->itemName << endl
            << setw(3) << " " << curr->itemDesc << endl << setw(3) << " " << "Quantity : " << curr->itemQuantity
            << endl << setw(3) << " " << "Price : $" << curr->itemPrice << endl << setw(3) << " " << "WholePrice : $" << curr->wholePrice
            << endl <<  setw(3) << " " << "Add Time : " << curr->timeChar << endl << endl;
            findFlag = true;
            findNum[findCount] = curr->itemNo;
            findCount++;
        }
        curr = curr->next;
    }
    if (findFlag == false)
    {
        cout << "Item not found!" << endl << endl;
    }
}
// A module to search items in list by whole price
void Inventory::searchItem2(Inventory* first, double searchWhole, int &findCount, int* (&findNum))
{
    bool findFlag = false;
    Inventory* curr = first;
    while (curr != nullptr)
    {
        if ((fabs(curr->wholePrice - searchWhole)) < 0.01)
        {
            cout << curr->itemNo << ". " << curr->itemName << endl
            << setw(3) << " " << curr->itemDesc << endl << setw(3) << " " << "Quantity : " << curr->itemQuantity
            << endl << setw(3) << " " << "Price : $" << curr->itemPrice << endl << setw(3) << " " << "WholePrice : $" << curr->wholePrice
            << endl <<  setw(3) << " " << "Add Time : " << curr->timeChar << endl << endl;
            findFlag = true;
            findNum[findCount] = curr->itemNo;
            findCount++;
        }
        curr = curr->next;
    }
    if (findFlag == false)
    {
        cout << "Item not found!" << endl << endl;
    }
}
// A module to search items in list by quantity
void Inventory::searchItem2(Inventory* first, int searchQuantity, int &findCount, int* (&findNum))
{
    bool findFlag = false;
    Inventory* curr = first;
    while (curr != nullptr)
    {
        if (curr->itemQuantity == searchQuantity)
        {
            cout << curr->itemNo << ". " << curr->itemName << endl
            << setw(3) << " " << curr->itemDesc << endl << setw(3) << " " << "Quantity : " << curr->itemQuantity
            << endl << setw(3) << " " << "Price : $" << curr->itemPrice << endl << setw(3) << " " << "WholePrice : $" << curr->wholePrice
            << endl <<  setw(3) << " " << "Add Time : " << curr->timeChar << endl << endl;
            findFlag = true;
            findNum[findCount] = curr->itemNo;
            findCount++;
        }
        curr = curr->next;
    }
    if (findFlag == false)
    {
        cout << "Item not found!" << endl << endl;
    }
}
// A module to edit an item in inventory list
void Inventory::editItem(Inventory* (&first), int editNum, char editType)
{
    bool findFlag = false;
    Inventory* curr = first;
    while ((curr != nullptr) && (findFlag == false))
    {
        if (curr->itemNo == editNum)
        {
            findFlag = true;
        }
        else
        {
            curr = curr->next;
        }
    }
    if (findFlag == true)
    {
        cout << "please enter new information >" << endl << endl;
        curr->addItem(editType);
    }
    else
    {
        cout << "Item not found!" << endl << endl;
    }
}
// A boolean function as program main menu
char Inventory::mainMenu()
{
    bool errorFlag = false;
    char userChoice;
    while ((userChoice != 'a') && (userChoice != 'e') && (userChoice != 'r') && (userChoice != 'd') && (userChoice != 's') && (userChoice != 'q'))
    {
        if (errorFlag == true)
        {
            cout << endl << "Invalid input! Please enter a character again >" << endl;
        }
        cout << "<a> Add an item" << endl << "<e> Edit item" << endl << "<r> Remove item" << endl
        << "<s> Search item" << endl  << "<d> Display all items" << endl << "<q> Quit" << endl;
        cout << endl << "> ";
        cin >> userChoice;
        cout << endl;
        errorFlag = true;
    }
    return userChoice;
}
// A module to search items in list by name
void Inventory::displayList(Inventory* first)
{
    Inventory* curr = first;
    cout << "Item List:" << endl << endl;
    while (curr != nullptr)
    {
        if (curr->firstItem == false)
        {
            cout << curr->itemNo << ". " << curr->itemName << endl
            << setw(3) << " " << curr->itemDesc << endl << setw(3) << " " << "Quantity : " << curr->itemQuantity
            << endl << setw(3) << " " << "Price : $" << curr->itemPrice << endl << setw(3) << " " << "WholePrice : $" << curr->wholePrice
            << endl <<  setw(3) << " " << "Add Time : " << curr->timeChar << endl << endl;
        }
        else
        {
            cout << "List is empty!" << endl << endl;
        }
        curr = curr->next;
    }
}
// A module to delete entire of linked list
void Inventory::deleteList(Inventory* (&last))
{
    Inventory* temp = nullptr;
    while (last->prev != nullptr)
    {
        temp = last;
        last = last->prev;
        delete temp;
        temp = nullptr;
    }
}
// A module to read items from file
void readFile (Inventory* (&last))
{
    istringstream buffer;
    string chQuantity, chPrice, chWhole;
    itemStruct item;
    FILE* fileBytes;
    long fileSize;
    fileBytes = fopen ("Inventory.bin","rb");
    fseek (fileBytes, 0, SEEK_END);
    fileSize = ftell(fileBytes);
    fclose (fileBytes);
    if (fileSize > 0)
    {
        ifstream readItem ("Inventory.bin");
        if (readItem.is_open())
        {

            do
            {
                getline (readItem, item.iName);
                if (item.iName.size() != 0)
                {
                    getline (readItem, item.iDesc);
                    getline (readItem, chQuantity);
                    buffer.clear();
                    buffer.str(chQuantity);
                    buffer >> item.iQuantity;
                    getline (readItem, chPrice);
                    buffer.clear();
                    buffer.str(chPrice);
                    buffer >> item.iPrice;
                    getline (readItem, chWhole);
                    buffer.clear();
                    buffer.str(chWhole);
                    buffer >> item.iWhole;
                    getline (readItem, item.tChar);
                    last->addNode(last);
                    last->addItem(item);
                }
            }
            while(!(readItem.eof()));
        }
        readItem.close();
    }
}
// A module to save items on file
void writeFile (Inventory* first)
{
    itemStruct item;
    Inventory* curr = first;
    ofstream writeItem ("Inventory.bin");
    if (writeItem.is_open())
    {
        while (curr != nullptr)
        {
            if (curr->firstItem == false)
            {
                item.iName = curr->itemName;
                item.iDesc = curr->itemDesc;
                item.iQuantity = curr->itemQuantity;
                item.iPrice = curr->itemPrice;
                item.iWhole = curr->wholePrice;
                item.tChar = curr->timeChar;
                writeItem << item.iName << endl << item.iDesc << endl << item.iQuantity << endl << item.iPrice
                << endl << item.iWhole << endl << item.tChar << endl;
                curr = curr->next;
            }
        }
    }
    writeItem.close();
}

int main()
{
    int* findNum;
    char userChoice, searchChoice, editConfirm, editChoice, deleteConfirm;
    char addType = 'a';
    string searchName, searchDesc;
    int searchNum, searchQuantity, editNum, deleteNum, findCount, index;
    double searchPrice, searchWhole;
    bool selectApproved, findFlag = false;
    Inventory* itemList = new Inventory;
    Inventory* first = itemList;
    Inventory* last = itemList;
    first->setFirstItem(true);
    last->setItemNo(1);
    readFile (last);
    cout << "<Inventory List>" << endl << endl;
    while (userChoice != 'q')
    {
        userChoice = last->mainMenu();
        switch (userChoice)
        {
            // Add an item
            case 'a':
            {
                last->addNode(last);
                last->addItem(addType);
                break;
            }
            // Edit an item
            case 'e':
            {
                findNum = (int*)malloc(sizeof(int));
                findCount = 0;
                editNum = 0;
                searchChoice = '?';
                editConfirm = '?';
                editChoice = '?';
                selectApproved = false;
                searchChoice = getSearchChoice();
                cin.ignore(1);
                if (searchChoice == 'n')
                {
                    searchNum = getQuantity('n');
                    cout << endl;
                    findFlag = last->searchItem(first ,searchNum);
                    if (findFlag == true)
                    {
                        while ((editConfirm != 'y') && (editConfirm != 'n'))
                        {
                            cout << "Do you want to edit this item <y/n> ? ";
                            cin >> editConfirm;
                            cout << endl;
                        }
                        if (editConfirm == 'y')
                        {
                            editChoice = getEditChoice();
                            cout << endl;
                            editNum = searchNum;
                            last->editItem(first ,editNum, editChoice);
                        }
                    }
                }
                else if (searchChoice == 'a')
                {
                    cout << "Please enter item name > ";
                    getline(cin, searchName);
                    cout << endl;
                    last->searchItem(first ,searchName, findCount, findNum);
                    if (findCount == 1)
                    {
                        while ((editConfirm != 'y') && (editConfirm != 'n'))
                        {
                            cout << "Do you want to edit this item <y/n> ? ";
                            cin >> editConfirm;
                            cout << endl;
                        }
                        if (editConfirm == 'y')
                        {
                            editChoice = getEditChoice();
                            cout << endl;
                            editNum = findNum[0];
                            last->editItem(first ,editNum, editChoice);
                        }
                    }
                    else if (findCount > 1)
                    {
                        while (selectApproved == false)
                        {
                            cout << "Please enter an item number to edit > ";
                            cin >> editNum;
                            for (index = 0; index < findCount; index++)
                            {
                                if (editNum == findNum[index])
                                {
                                    selectApproved = true;
                                }
                            }
                        }
                        while ((editConfirm != 'y') && (editConfirm != 'n'))
                        {
                            cout << "Do you want to edit this item <y/n> ? ";
                            cin >> editConfirm;
                            cout << endl;
                        }
                        if (editConfirm == 'y')
                        {
                            editChoice = getEditChoice();
                            cout << endl;
                            last->editItem(first ,editNum, editChoice);
                        }
                    }
                }
                else if (searchChoice == 'd')
                {
                    cout << "Please enter item description > ";
                    getline(cin, searchDesc);
                    cout << endl;
                    last->searchItem2(first ,searchDesc, findCount, findNum);
                    if (findCount == 1)
                    {
                        while ((editConfirm != 'y') && (editConfirm != 'n'))
                        {
                            cout << "Do you want to edit this item <y/n> ? ";
                            cin >> editConfirm;
                            cout << endl;
                        }
                        if (editConfirm == 'y')
                        {
                            editChoice = getEditChoice();
                            cout << endl;
                            editNum = findNum[0];
                            last->editItem(first ,editNum, editChoice);
                        }
                    }
                    else if (findCount > 1)
                    {
                        while (selectApproved == false)
                        {
                            cout << "Please enter an item number to edit > ";
                            cin >> editNum;
                            for (index = 0; index < findCount; index++)
                            {
                                if (editNum == findNum[index])
                                {
                                    selectApproved = true;
                                }
                            }
                        }
                        while ((editConfirm != 'y') && (editConfirm != 'n'))
                        {
                            cout << "Do you want to edit this item <y/n> ? ";
                            cin >> editConfirm;
                            cout << endl;
                        }
                        if (editConfirm == 'y')
                        {
                            editChoice = getEditChoice();
                            cout << endl;
                            last->editItem(first ,editNum, editChoice);
                        }
                    }
                }
                else if (searchChoice == 'q')
                {
                    searchQuantity = getQuantity('q');
                    cout << endl;
                    last->searchItem2(first ,searchQuantity, findCount, findNum);
                    if (findCount == 1)
                    {
                        while ((editConfirm != 'y') && (editConfirm != 'n'))
                        {
                            cout << "Do you want to edit this item <y/n> ? ";
                            cin >> editConfirm;
                            cout << endl;
                        }
                        if (editConfirm == 'y')
                        {
                            editChoice = getEditChoice();
                            cout << endl;
                            editNum = findNum[0];
                            last->editItem(first ,editNum, editChoice);
                        }
                    }
                    else if (findCount > 1)
                    {
                        while (selectApproved == false)
                        {
                            cout << "Please enter an item number to edit > ";
                            cin >> editNum;
                            for (index = 0; index < findCount; index++)
                            {
                                if (editNum == findNum[index])
                                {
                                    selectApproved = true;
                                }
                            }
                        }
                        while ((editConfirm != 'y') && (editConfirm != 'n'))
                        {
                            cout << "Do you want to edit this item <y/n> ? ";
                            cin >> editConfirm;
                            cout << endl;
                        }
                        if (editConfirm == 'y')
                        {
                            editChoice = getEditChoice();
                            cout << endl;
                            last->editItem(first ,editNum, editChoice);
                        }
                    }
                }
                else if (searchChoice == 'p')
                {
                    searchPrice = getPrice();
                    cout << endl;
                    last->searchItem(first ,searchPrice, findCount, findNum);
                    if (findCount == 1)
                    {
                        while ((editConfirm != 'y') && (editConfirm != 'n'))
                        {
                            cout << "Do you want to edit this item <y/n> ? ";
                            cin >> editConfirm;
                            cout << endl;
                        }
                        if (editConfirm == 'y')
                        {
                            editChoice = getEditChoice();
                            cout << endl;
                            editNum = findNum[0];
                            last->editItem(first ,editNum, editChoice);
                        }
                    }
                    else if (findCount > 1)
                    {
                        while (selectApproved == false)
                        {
                            cout << "Please enter an item number to edit > ";
                            cin >> editNum;
                            for (index = 0; index < findCount; index++)
                            {
                                if (editNum == findNum[index])
                                {
                                    selectApproved = true;
                                }
                            }
                        }
                        while ((editConfirm != 'y') && (editConfirm != 'n'))
                        {
                            cout << "Do you want to edit this item <y/n> ? ";
                            cin >> editConfirm;
                            cout << endl;
                        }
                        if (editConfirm == 'y')
                        {
                            editChoice = getEditChoice();
                            cout << endl;
                            last->editItem(first ,editNum, editChoice);
                        }
                    }
                }
                else if (searchChoice == 'w')
                {
                    cout << "Please enter item whole price > ";
                    cin >> searchWhole;
                    cout << endl;
                    last->searchItem2(first ,searchWhole, findCount, findNum);
                    if (findCount == 1)
                    {
                        while ((editConfirm != 'y') && (editConfirm != 'n'))
                        {
                            cout << "Do you want to edit this item <y/n> ? ";
                            cin >> editConfirm;
                            cout << endl;
                        }
                        if (editConfirm == 'y')
                        {
                            editChoice = getEditChoice();
                            cout << endl;
                            editNum = findNum[0];
                            last->editItem(first ,editNum, editChoice);
                        }
                    }
                    else if (findCount > 1)
                    {
                        while (selectApproved == false)
                        {
                            cout << "Please enter an item number to edit > ";
                            cin >> editNum;
                            for (index = 0; index < findCount; index++)
                            {
                                if (editNum == findNum[index])
                                {
                                    selectApproved = true;
                                }
                            }
                        }
                        while ((editConfirm != 'y') && (editConfirm != 'n'))
                        {
                            cout << "Do you want to edit this item <y/n> ? ";
                            cin >> editConfirm;
                            cout << endl;
                        }
                        if (editConfirm == 'y')
                        {
                            editChoice = getEditChoice();
                            cout << endl;
                            last->editItem(first ,editNum, editChoice);
                        }
                    }
                }
                break;
            }
            // Delete an item from list
            case 'r':
            {
                findNum = (int*)malloc(sizeof(int));
                findCount = 0;
                deleteNum = 0;
                searchChoice = '?';
                deleteConfirm = '?';
                selectApproved = false;
                searchChoice = getSearchChoice();
                cin.ignore(1);
                if (searchChoice == 'n')
                {
                    searchNum = getQuantity('n');
                    cout << endl;
                    findFlag = last->searchItem(first ,searchNum);
                    if (findFlag == true)
                    {
                        while ((deleteConfirm != 'y') && (deleteConfirm != 'n'))
                        {
                            cout << "Do you want to remove this item <y/n> ? ";
                            cin >> deleteConfirm;
                            cout << endl;
                        }
                        if (deleteConfirm == 'y')
                        {
                            cout << endl;
                            deleteNum = searchNum;
                            last->deleteItem(first, last, deleteNum);
                        }
                    }
                }
                else if (searchChoice == 'a')
                {
                    cout << "Please enter item name > ";
                    getline(cin, searchName);
                    cout << endl;
                    last->searchItem(first ,searchName, findCount, findNum);
                    if (findCount == 1)
                    {
                        while ((deleteConfirm != 'y') && (deleteConfirm != 'n'))
                        {
                            cout << "Do you want to remove this item <y/n> ? ";
                            cin >> deleteConfirm;
                            cout << endl;
                        }
                        if (deleteConfirm == 'y')
                        {
                            cout << endl;
                            deleteNum = findNum[0];
                            last->deleteItem(first, last, deleteNum);
                        }
                    }
                    else if (findCount > 1)
                    {
                        while (selectApproved == false)
                        {
                            cout << "Please enter an item number to remove > ";
                            cin >> deleteNum;
                            for (index = 0; index < findCount; index++)
                            {
                                if (deleteNum == findNum[index])
                                {
                                    selectApproved = true;
                                }
                            }
                        }
                        while ((deleteConfirm != 'y') && (deleteConfirm != 'n'))
                        {
                            cout << "Do you want to remove this item <y/n> ? ";
                            cin >> deleteConfirm;
                            cout << endl;
                        }
                        if (deleteConfirm == 'y')
                        {
                            cout << endl;
                            last->deleteItem(first, last, deleteNum);
                        }
                    }
                }
                else if (searchChoice == 'd')
                {
                    cout << "Please enter item description > ";
                    getline(cin, searchDesc);
                    cout << endl;
                    last->searchItem2(first ,searchDesc, findCount, findNum);
                    if (findCount == 1)
                    {
                        while ((deleteConfirm != 'y') && (deleteConfirm != 'n'))
                        {
                            cout << "Do you want to remove this item <y/n> ? ";
                            cin >> deleteConfirm;
                            cout << endl;
                        }
                        if (deleteConfirm == 'y')
                        {
                            cout << endl;
                            deleteNum = findNum[0];
                            last->deleteItem(first, last, deleteNum);
                        }
                    }
                    else if (findCount > 1)
                    {
                        while (selectApproved == false)
                        {
                            cout << "Please enter an item number to remove > ";
                            cin >> deleteNum;
                            for (index = 0; index < findCount; index++)
                            {
                                if (deleteNum == findNum[index])
                                {
                                    selectApproved = true;
                                }
                            }
                        }
                        while ((deleteConfirm != 'y') && (deleteConfirm != 'n'))
                        {
                            cout << "Do you want to remove this item <y/n> ? ";
                            cin >> deleteConfirm;
                            cout << endl;
                        }
                        if (deleteConfirm == 'y')
                        {
                            cout << endl;
                            last->deleteItem(first, last, deleteNum);
                        }
                    }
                }
                else if (searchChoice == 'q')
                {
                    searchQuantity = getQuantity('q');
                    cout << endl;
                    last->searchItem2(first ,searchQuantity, findCount, findNum);
                    if (findCount == 1)
                    {
                        while ((deleteConfirm != 'y') && (deleteConfirm != 'n'))
                        {
                            cout << "Do you want to remove this item <y/n> ? ";
                            cin >> deleteConfirm;
                            cout << endl;
                        }
                        if (deleteConfirm == 'y')
                        {
                            cout << endl;
                            deleteNum = findNum[0];
                            last->deleteItem(first, last, deleteNum);
                        }
                    }
                    else if (findCount > 1)
                    {
                        while (selectApproved == false)
                        {
                            cout << "Please enter an item number to remove > ";
                            cin >> deleteNum;
                            for (index = 0; index < findCount; index++)
                            {
                                if (deleteNum == findNum[index])
                                {
                                    selectApproved = true;
                                }
                            }
                        }
                        while ((deleteConfirm != 'y') && (deleteConfirm != 'n'))
                        {
                            cout << "Do you want to remove this item <y/n> ? ";
                            cin >> deleteConfirm;
                            cout << endl;
                        }
                        if (deleteConfirm == 'y')
                        {
                            cout << endl;
                            last->deleteItem(first, last, deleteNum);
                        }
                    }
                }
                else if (searchChoice == 'p')
                {
                    searchPrice = getPrice();
                    cout << endl;
                    last->searchItem(first ,searchPrice, findCount, findNum);
                    if (findCount == 1)
                    {
                        while ((deleteConfirm != 'y') && (deleteConfirm != 'n'))
                        {
                            cout << "Do you want to remove this item <y/n> ? ";
                            cin >> deleteConfirm;
                            cout << endl;
                        }
                        if (deleteConfirm == 'y')
                        {
                            cout << endl;
                            deleteNum = findNum[0];
                            last->deleteItem(first, last, deleteNum);
                        }
                    }
                    else if (findCount > 1)
                    {
                        while (selectApproved == false)
                        {
                            cout << "Please enter an item number to remove > ";
                            cin >> deleteNum;
                            for (index = 0; index < findCount; index++)
                            {
                                if (deleteNum == findNum[index])
                                {
                                    selectApproved = true;
                                }
                            }
                        }
                        while ((deleteConfirm != 'y') && (deleteConfirm != 'n'))
                        {
                            cout << "Do you want to remove this item <y/n> ? ";
                            cin >> deleteConfirm;
                            cout << endl;
                        }
                        if (deleteConfirm == 'y')
                        {
                            cout << endl;
                            last->deleteItem(first, last, deleteNum);
                        }
                    }
                }
                else if (searchChoice == 'w')
                {
                    cout << "Please enter item whole price > ";
                    cin >> searchWhole;
                    cout << endl;
                    last->searchItem2(first ,searchWhole, findCount, findNum);
                    if (findCount == 1)
                    {
                        while ((deleteConfirm != 'y') && (deleteConfirm != 'n'))
                        {
                            cout << "Do you want to remove this item <y/n> ? ";
                            cin >> deleteConfirm;
                            cout << endl;
                        }
                        if (deleteConfirm == 'y')
                        {
                            cout << endl;
                            deleteNum = findNum[0];
                            last->deleteItem(first, last, deleteNum);
                        }
                    }
                    else if (findCount > 1)
                    {
                        while (selectApproved == false)
                        {
                            cout << "Please enter an item number to remove > ";
                            cin >> deleteNum;
                            for (index = 0; index < findCount; index++)
                            {
                                if (deleteNum == findNum[index])
                                {
                                    selectApproved = true;
                                }
                            }
                        }
                        while ((deleteConfirm != 'y') && (deleteConfirm != 'n'))
                        {
                            cout << "Do you want to remove this item <y/n> ? ";
                            cin >> deleteConfirm;
                            cout << endl;
                        }
                        if (deleteConfirm == 'y')
                        {
                            cout << endl;
                            last->deleteItem(first, last, deleteNum);
                        }
                    }
                }
                break;
            }
            // Search for items in list
            case 's':
            {
                char searchChoice = '?';
                findCount = 0;
                findNum = (int*)malloc(sizeof(int));
                searchChoice = getSearchChoice();
                cin.ignore(1);
                if (searchChoice == 'n')
                {
                    searchNum = getQuantity('n');
                    cout << endl;
                    findFlag = last->searchItem(first ,searchNum);
                }
                else if (searchChoice == 'a')
                {
                    cout << "Please enter item name > ";
                    getline(cin, searchName);
                    cout << endl;
                    last->searchItem(first ,searchName, findCount, findNum);
                }
                else if (searchChoice == 'd')
                {
                    cout << "Please enter item description > ";
                    getline(cin, searchDesc);
                    cout << endl;
                    last->searchItem2(first ,searchDesc, findCount, findNum);
                }
                else if (searchChoice == 'q')
                {
                    searchQuantity = getQuantity('q');
                    cout << endl;
                    last->searchItem2(first ,searchQuantity, findCount, findNum);
                }
                else if (searchChoice == 'p')
                {
                    searchPrice = getPrice();
                    cout << endl;
                    last->searchItem(first ,searchPrice, findCount, findNum);
                }
                else if (searchChoice == 'w')
                {
                    cout << "Please enter item whole price > ";
                    cin >> searchWhole;
                    cout << endl;
                    last->searchItem2(first ,searchWhole, findCount, findNum);
                }
                break;
            }
            // Display entire list
            case 'd':
            {
                last->displayList(first);
                break;
            }
        }
    }
    // Save item list on file
    writeFile (first);
    // Delete entire of list
    itemList->deleteList(last);
    delete last;
    last = nullptr;
    // Delete a dynamic integer array
    delete findNum;
    findNum = nullptr;
    return 0;
}
