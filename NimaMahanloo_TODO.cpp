// NimaMahanloo_TODO.cpp
// CISP 400 - TODO
// FLC - Professor Fowler
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
// Program main class
class ToDo
{
    public:
        ToDo();
        ToDo(string strInput, int num);
        // + operator overloading
        friend void operator+(vector <ToDo> (&toDoList), string inStr);
        // - opetator overloading
        friend void operator-(vector <ToDo> (&toDoList), int itemNum);
        // << operator overloading
        friend void operator<<(vector <ToDo> toDoList, int &sSize);
        int getItemNum() {return itemNum;}
        void setItemNum(int iNum) {itemNum = iNum;}
        string getStr() {return str;}
        void setStr(string inString) {str = inString;}
        // Greeting : Program main menu interface
        char mainMenu(vector <ToDo> (&toDoList));
    protected:
        string str;
        int itemNum;
};

ToDo::ToDo()
{
    str = "";
    itemNum = -1;
}

ToDo::ToDo(string strInput, int num)
{
    str = strInput;
    itemNum  = num;
}
// Feature 1
// Recursive module for str to int conversion process multiply rate adjust
void rateAdjuster(int index, int &rate, int &i)
{
    if (index == 1)
    {
        rate = 1;
    }
    else if ((index > 1) && (i < index))
    {
        rate *= 10;
        ++i;
        // Ditect call recursion module
        rateAdjuster(index, rate, i);
    }
}
// Feature 2
// Recursive module to convert input string to integer value
void indexNum (string tempNum, int &num, int &rate, int &i)
{
	if (i < tempNum.size())
	{
	      char tempChar = tempNum[i];
          num += (int(tempChar)-48) * rate;
          rate /= 10;
          i++;
          // Direct call recursion module 
          indexNum (tempNum, num, rate, i);
	}
}
// Feature 3
// Reursive module to adjust TODO list item numbers after removing an item
void numAdjuster(vector <ToDo> (&toDoList), int &i)
{
	if (i < toDoList.size())
	{
		toDoList[i].setItemNum (toDoList[i].getItemNum() - 1);
	i++;
	// Direct call recursion module
	numAdjuster(toDoList, i);
	}
}
// Specification 1
// Overloaded operator + module to add an element to vector as object
void operator+(vector <ToDo> (&toDoList), string inStr)
    {
        int strSize, iNum;
        strSize = 0;
        string tempStr = inStr.substr(1, inStr.size()-1);
        iNum = toDoList.size()+1;
        ToDo temp(tempStr, iNum);
        toDoList.push_back(temp);
    }
// Specification 3
// Overloaded opetator - module to remove an element from vector
void operator-(vector <ToDo> (&toDoList), string inStr)
    {
        int num = 0, index, i, rate;
        string tempNum = inStr.substr(1, inStr.size()-1);
        index = tempNum.size();
        if (index > 0)
        {
            i = 1;
            rate = 1;
            char tempChar;
            // Call recursion module to adjust proper start multiply rate for string to integer convert ptocess
            rateAdjuster(index, rate, i);
            i = 0;
            // Call recursion module to convert input string to integer
            indexNum (tempNum, num, rate, i);
        }
        num--;
        if (num >= toDoList.size())
        {
            cout << "Error: Invalid item number!" << endl; 
            return;
        }
        // Feature 5
        // Assertion feature to validate user input about item number to delete
        assert(num < toDoList.size());
  toDoList.erase(toDoList.begin()+(num));
         i = num;
        // Call recursion module to adjust TODO list item numbers after an item delete
        numAdjuster (toDoList, i);
 }
// Specification 2 + Feature 4
// Recursive overloaded opetator << module to display entire of TODO list
void operator<<(vector <ToDo> toDoList, int &sSize)
{
	if (toDoList.size() > 0)
	{
        if(sSize < toDoList.size())
        {
                cout << toDoList[sSize].itemNum << ": " << toDoList[sSize].str << endl;
                sSize++;
                // Direct call recursive operator overloaded << function 
                toDoList << sSize;
        }
        else
        {
            cout << endl;
        }
	}
	else
	{
		cout << "List is empty!" << endl << endl;
	}
 }
// Program greeting : Character module as program main menu
char ToDo::mainMenu(vector <ToDo> (&toDoList))
{
	menu :
    int strSize, inputSize, j;
    string inStr = "**";
    bool errorFlag = false;
    // Soecification 5 for quit command as 'q'
    cout << "+ ToDo : Add a new ToDo item to list" << endl
    << "? : Show all ToDo items in list" << endl
    << "- item number : Remove item from the list" << endl << "/ ";
    while (((inStr[0] != '+') || ((inStr[0] == '+') && (inStr[1] == '\0'))) && ((inStr[0] != '-') || ((inStr[0] == '-') && (inStr[1] == '\0'))) && (inStr[0] != '?') && (inStr[0] != 'q'))
    {
        if (errorFlag == true)
        {
            cout << "Error: Inavalid command!" << endl << "/ ";
        }
        getline(cin, inStr);
        errorFlag = true;
    }
    //Feature 5
    // Assertion feature for input validation
    assert(((inStr[0] == '+') && (inStr[1] != '\0')) || ((inStr[0] == '-') && (inStr[1] != '\0')) || (inStr[0] == '?') || (inStr[0] == 'q'));
    if (inStr[0] == '+')
    {
        cout << endl;
        toDoList + inStr;
    }
    else if (inStr[0] == '?')
    {
        int sSize = 0;
        cout << endl << "TODO List Tasks:" << endl << endl;
        toDoList << sSize;
    }
    else if (inStr[0] == '-')
    {
    	for (j = 1; j < inStr.size(); j++)
    	{
    		if (!(isdigit(inStr[j])))
    		{
    			cout << "Error : Invalid item number!" << endl;
    			goto menu;
    		}
    		    // Feature 5
    			// Assertion feature to vaidate input item number by user
    			assert(isdigit(inStr[j]));
    	}
        cout << endl;
        toDoList - inStr;
    }
    return inStr[0];
}
// Specification 4
// Module to read stored items from file
void readFile (vector <ToDo> (&toDoList))
{
	int numGen = 1;
	string strFile;
	ToDo temp;
	ifstream loadToDo ("data.txt");
	if (loadToDo.is_open())
	{
		while (!(loadToDo.eof()))
		{
			loadToDo >> strFile;
			temp.setItemNum(numGen);
			temp.setStr(strFile);
			toDoList.push_back(temp);
			numGen++;
		}
	}
	loadToDo.close();
}
// Specification 4
// Module to save TODO items on file
void writeFile (vector<ToDo> toDoList)
{
	int i = 0;
	ofstream saveToDo("data.txt");
	if (saveToDo.is_open())
	{
		while (i < toDoList.size())
		{
			if (i < toDoList.size()-1)
			{
				saveToDo << toDoList.at(i).getStr() << endl;
			}
			else
			{
				saveToDo << toDoList.at(i).getStr();
			}
	        i++;
		}
	}
	saveToDo.close();
}

int main()
{
    int item = 0;
    char command = '0';
    vector <ToDo> toDoList;
    readFile(toDoList);
    cout << "<TODO List>" << endl << endl;
    // Specification 5 for quit command as 'q'
    while (command != 'q')
    {
        command = toDoList[item].mainMenu(toDoList);
    }
    writeFile(toDoList);
    return 0;
}