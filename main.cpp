/*****************************************************************
//
//  NAME:        Kason Shiroma
//
//  HOMEWORK:    project1
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        March 3, 2019
//
//  FILE:        userinterface.c
//
//  DESCRIPTION:
//   This file contains the user-interface functions for the menu 
//    of project1 - The Bank Database Application
//
****************************************************************/

#include <iostream> 
#include <string>
#include <cstring>
#include "record.h"
#include "llist.h"

using namespace std;

/*****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   A userinterface function
//                 This function obtains the information about the menu
//                  from the user
//
//  Parameters:    argc (int) 
//                 argv (char**)
//
//  Return values:  0 : success
//
****************************************************************/

int main(int argc, char *argv[])
{   
    llist mylist;
    char option;
    int runMenu;
    int accno;
    char name[25];              
    char address[80];
    char buffer[100];
    int validInput;
    int enterInfo;
    char correctInput;
    int checkCorrect;
    int success;

    runMenu = 0;
    enterInfo = 1;                
    checkCorrect = 1;  
    success = -1;

    runMenu = 1;

    #ifdef DEBUG
        cout << "\n****DEBUG MODE IS ON****\n\n"; 
    #endif

    cout << "\nHello, this is the Bank Database Application\n"
            "    which contains information on your account.\n\n";

    while (runMenu == 1)
    { 
        cout << "Choose an option by entering the corresponding number below:\n"
                "1. Add a record\n"
                "2. Print a record\n"
                "3. Print all records\n"
                "4. Find a record\n"
                "5. Delete a record\n"
                "6. Reverse the list\n"
                "7. Exit\n\n";

        cin >> option;
        cin.ignore(100, '\n');
        cout << "\n";

        /* addRecord */        
        if (option == '1')
        {
            enterInfo = 1;
            checkCorrect = 1;

            cout << "You chose to add a record.\n";
                
            /* account number */
            while (enterInfo == 1)
            {
                cin.clear();
                cout << "Enter your account number: ";
                cin >> accno; 
                
                if (!cin)
                {
                    enterInfo = 1;
                    checkCorrect = 0;            
 
                    cout << "\n**Error** Not a valid integer for your account number.\n"
                            "    Please try again.\n\n";

                    cin.clear();
                    cin.ignore(100, '\n');
                }

                else
                {
                    enterInfo = 0;
                    cin.ignore(100, '\n');
                }
            }

            enterInfo = 1;
        
            /* name */
            while (enterInfo == 1)
            {
                cout << "\nEnter your name: ";
                cin.getline(name, 80);
           
                if (strlen(name) <= 25)
                {
                    enterInfo = 0;
                }
                
                else
                {
                    enterInfo = 1;
 
                    cout << "**Error** You must enter 24 characters or less. Please re-enter.\n";
                }
            } 

            enterInfo = 1;
                
            /* address */
            while (enterInfo == 1)
            {
                cout << "\nEnter your multiline address, press ';' and enter to end input:\n";
                cin.getline(address, 80, ';'); 
                cin.ignore(100, '\n');

                if (strlen(address) <= 80)
                {
                    enterInfo = 0;       
                }    

                else
                {
                    enterInfo = 1;

                    cout << "**Error** You must enter 49 characters or less. Please re-enter.\n";
                }
            }

            checkCorrect = 1;

            while (checkCorrect == 1)
            {
                cout << "\nIs this correct? (Y/N)" << endl;
                cout << "account number: " << accno << endl;
                cout << "name: " << name << endl;
                cout << "address: " << endl;
                cout << address << endl;
                cin >> correctInput;
                cin.ignore(100, '\n');

                if (correctInput == 'Y' || correctInput == 'y')
                {
                    checkCorrect = 0;
                    enterInfo = 1;
                }
                else if (correctInput == 'N' || correctInput == 'n')
                {
                    checkCorrect = 0;
                    enterInfo = 0;
                    success = 1;
                }
                else
                {
                    cout << "\nNot a valid response, please re-enter.\n";

                    checkCorrect = 1;
                    enterInfo = 0;
                }
            }
        
            if (enterInfo == 1)
            {
                success = mylist.addRecord(accno, name, address);
            }

            if (success == 0)
            {
                cout << "\nSuccessfully added record.\n\n";
            }
            
            else
            {
                cout << "\nCould not add the record.\n\n";
            }
        }

        /* printRecord */
        else if (option == '2')
        {
            enterInfo = 1;

            cout << "You chose to print a record.\n";
    
            while (enterInfo == 1)
            {
                cout << "Enter the account number of the record to be printed: ";
                cin >> accno;
                cin.clear();
                cin.ignore(100, '\n');
                cout << "\n";

                if (cin.fail())   
                {
                    enterInfo = 1;

                    cout << "**Error** Not a valid integer for your account number.\n"
                            "    Please try again.\n";
                }

                else
                {
                    success = mylist.printRecord(accno);            
                    enterInfo = 0;
                }
            }

            if (success == 0)
            {
                cout << "Successfully printed the record.\n\n";
            }

            else
            {       
                cout << "Could not print the record.\n\n";
            }
        }

        /* printAllRecords */
        else if (option == '3')
        {
            cout << "You chose to print all the records.\n";
            cout << mylist;
            cout << "All records successfully printed.\n\n";
        }

        /* findRecords */
        else if (option == '4') 
        {
            enterInfo = 1;

            cout << "You chose to search for a record.\n";
 
            while (enterInfo == 1)
            {
                cout << "Enter the first name of the record to find: ";
                cin.getline(name, 80);
                cout << "\n";

                if (strlen(name) <= 25)
                {                 
                    enterInfo = 0;
                }

                else
                {                 
                    enterInfo = 1;

                    cout << "**Error** You must enter 24 characters or less. Please re-enter.\n";
                }
            }
           
            if (enterInfo == 0)
            {
                cout << "\n";
                success = mylist.findRecords(name);
            }

            if (success == 0)
            {
                cout << "Successfully found the record.\n\n";
            }

            else
            {
                cout << "Could not find the record.\n\n";
            }
        }

        /* deleteRecord */
        else if (option == '5')
        {
            enterInfo = 1;

            cout << "You chose to delete a record.\n";

            while (enterInfo == 1)
            {
                checkCorrect = 1;

                cout << "Enter the account number of the record to delete: ";
                cin >> accno;
                cin.clear();
                cin.ignore(100, '\n');
                cout << "\n";

                if (cin.fail())
                {
                    enterInfo = 1;
                    checkCorrect = 0;

                    cout << "**Error** Not a valid integer for your account number.\n"
                            "    Please try again.\n";
                }

                else                 
                {               
                     enterInfo = 0;
                     checkCorrect = 1;
                }
 
                while (checkCorrect == 1)
                {
                    cout << "Is " << accno << "  correct? (Y/N)\n";
                    cin >> correctInput;
                    cin.ignore(100, '\n');

                    if (correctInput == 'Y' || correctInput == 'y')
                    {
                        char deleteCheck;
                        int cont;                        

                        cont = 1;

                        while (cont == 1)
                        {
                            cout << "Are you sure you want to delete record " << accno << "? (Y/N)\n";
                            cin >> deleteCheck;
                            cin.ignore(100, '\n');

                            if (deleteCheck == 'Y' || deleteCheck == 'y')
                            {
                                cont = 0;
                                enterInfo = 0;
                                checkCorrect = 0;

                                success = mylist.deleteRecord(accno);
                            }

                            else if (deleteCheck == 'N' || deleteCheck == 'n')
                            {
                                cont = 0;
                                enterInfo = 0;           
                                checkCorrect = 0;
                            }

                            else
                            {
                                cout << "Not a valid response, please re-enter.\n";

                                cont = 1;
                                enterInfo = 0;
                                checkCorrect = 0;
                            }
                        }
                    }

                    else if (correctInput == 'N' || correctInput == 'n')
                    {
                        enterInfo = 1;
                        checkCorrect = 0;
                    }

                    else
                    {
                        cout << "Not a valid response, please re-enter.\n";
                    
                        enterInfo = 1;       
                        checkCorrect = 1;     
                    }
                }
            }

            if (success == 0)
            {
                cout << "\nSuccessfully deleted the record.\n\n";
            }

            else
            {
                cout << "\nCould not delete the record.\n\n";
            }            
        }    

        /*reverse*/
        else if (option == '6')
        {
            mylist.reverse();

            cout << "Successfully reversed all records.\n\n";
        }
        
        /* exit */
        else if (option == '7')
        {
            runMenu = 0;
        }
    }

    return 0;
}

