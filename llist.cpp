/*****************************************************************
//
//  NAME:        Kason Shiroma
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 12, 2019
//
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   This file contains the driver and the user-interface functions
//
****************************************************************/

#include <fstream>
#include <iostream>
#include <cstring>
#include "record.h"
#include "llist.h"

#ifndef DEBUG
    #define DEBUG
#endif

using namespace std;

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   This is the constructor for llist that creates a
//                  file and sets start to null.
//
****************************************************************/

llist::llist()
{
    #ifdef DEBUG
        cout << "\n***********DEBUG INFO**************\n"
                   "llist constructor was called\n"
                   "there are no parameters\n"
                   "***********************************\n\n";

    #endif

    strcpy(filename, "records.txt");  
    start = NULL;
    readfile();
} 

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   This is the constructor for llist that creates a
//                  file with the name from the user and sets start to null.
//
//  Parameters:    fn (char[]) : the name of the file from the user
//
****************************************************************/

llist::llist(char fn[])
{
    #ifdef DEBUG
        cout << "\n***********DEBUG INFO**************\n"           
                "llist constructor was called\n"
                "parameter is fn (char[])\n"           
                "***********************************\n\n";

    #endif

    strcpy(filename, fn);
    start = NULL;
    readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   This is the destructor for llist that cleans the heap 
//
//  Parameters:    fn (char[]) : the name of the file from the user
//
****************************************************************/

llist::~llist()
{
    #ifdef DEBUG               
        cout << "\n***********DEBUG INFO**************\n"
                "llist destructor was called\n"
                "there are no parameters\n"
                "***********************************\n\n";

    #endif

    writefile();
    cleanup();
}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   This function adds a new record at the end of the list.
//                 Doesn't accept duplicate account numbers.
//
//  Parameters:    uaccno (int) : the account number of the new record
//                 uname (char[]) : the name of the new record
//                 uaddress (char[]) : the address of the new record
//
//  Return values:  0 : success
//                 -1 : could not add the record (may have duplicate account number)
//
****************************************************************/

int llist::addRecord(int uaccno, char uname[], char uaddress[])
{
    struct record *newRecord;
    struct record *temp;
    struct record *prev;
    int returnVal;

    temp = NULL;
    prev = NULL;
    returnVal = 0;
    newRecord = new struct record;
    newRecord->accountno = uaccno; 
    strcpy(newRecord->name, uname);
    strcpy(newRecord->address, uaddress);

    #ifdef DEBUG
        cout << "\n***********DEBUG INFO**************\n"
                "addRecord was called\n"
                "parameters are uaccno (int): " << uaccno << ", uname (char[]): " << uname <<
                ", address (char[]):\n" << uaddress << "\n***********************************\n\n";
    #endif

    if (start == NULL)
    {
        start = newRecord;
        newRecord->next = NULL;
        returnVal = 0;
    }

    else
    {
        prev = start;
        temp = prev->next;

        if (newRecord->accountno == prev->accountno)
        {
            returnVal = -1;
        }

        while (temp != NULL)
        {
            if (newRecord->accountno == temp->accountno)
            {
                returnVal = -1;
            }
        
            prev = temp;
            temp = temp->next;
        }
    
        if (returnVal != -1)
        {
            prev->next = newRecord;
            newRecord->next = NULL;
            temp = newRecord;
            returnVal = 0;
        }
    }

    return returnVal;
}

/*****************************************************************             
//
//  Function name: printRecord
//
//  DESCRIPTION:   This function prints the record with the matching account number
//                
//  Parameter:    uaccno (int) : the account number of the record to print
//
//  Return values:  0 : success   
//                 -1 : could not print the record
//
****************************************************************/

int llist::printRecord(int uaccno)
{
    #ifdef DEBUG
        cout << "\n***********DEBUG INFO**************\n"
                "printRecord was called\n"
                "parameter is uaccno (int): " << uaccno << "\n"
                "***********************************\n\n";
    #endif

    struct record *temp;       
    int returnVal;

    if (start == NULL)
    {
        cout << "The list is empty.\n";
        returnVal = -1;
    }

    else
    {
        temp = start;  
        returnVal = 1;   


        while (temp != NULL)
        {         
            if (temp->accountno == uaccno)             
            {
                cout << "account number: " << temp->accountno << endl;
                cout << "name: " << temp->name << endl;
                cout << "address:\n" << temp->address << "\n\n";

                returnVal = 0;
            }                

            temp = temp->next;
        }
    }

    return returnVal;
}

/*****************************************************************
//
//  Function name: operator<<    
//
//  DESCRIPTION:   This function overloads the operator<< to print all
//                  records in the list
//
//  Parameters:    os (ostream&) : the  ostream object 
//                 mylist (llist&) : the list object
//
//  Return value:  the output stream
//
****************************************************************/

ostream& operator<<(ostream& os, llist& list)
{

    #ifdef DEBUG
        cout << "\n***********DEBUG INFO**************\n" 
                "operator<< was called\n"  
                "parameters are os (ostream&) and list (llist&)\n"  
                "***********************************\n\n";
    #endif

    struct record *temp;
    temp = list.start;

    while (temp != NULL)
    {
        os << "account number: " << temp->accountno << endl
           << "name: " << temp->name << endl
           << "address: \n" <<  temp->address << "\n\n";
    
        temp = temp->next;
    }

    return os;
}

/*****************************************************************
//
//  Function name: findRecords
//
//  DESCRIPTION:   This function will print the record(s) with names
//                  starting with the given string as a key
//
//  Parameters:    start (struct record *) : points to the start of the list
//                 uname (char[]) : the name to use as a key
//
//  Return values:  0 : success
//                 -1 : could not find the record(s)
//
****************************************************************/

int llist::findRecords(char uname[])
{
    #ifdef DEBUG 
        cout << "\n***********DEBUG INFO**************\n"
                "findRecords was called\n"
                "parameter is uname (char[]): " << uname << "\n"
                "***********************************\n\n"; 
    #endif  

    struct record *temp;      
    int unamelen;            
    int returnVal;

    unamelen = strlen(uname);

    if (start == NULL)
    {                
        cout << "The list is empty.\n";
        returnVal = -1;
    }

    else
    {
        temp = start;
        returnVal = -1;

        while (temp != NULL)
        {          
            if (strncmp(temp->name, uname, unamelen) == 0)       
            {
                cout << "account number: " << temp->accountno << endl;
                cout << "name: " << temp->name << endl;
                cout << "address:\n" << temp->address << "\n\n";

                returnVal = 0;
            }


            temp = temp->next;
        }
     }

    return returnVal;
}

/*****************************************************************
//
//  Function name: deleteRecord
//
//  DESCRIPTION:   This function will delete the record witht the specified account number.
//
//  Parameters:    start (struct record **) : points to the address of the start of the list
//                 uaccno (int) : the account number of the record to delete
//
//  Return values:  0 : success
//                 -1 : could not delete the record 
//
****************************************************************/

int llist::deleteRecord(int uaccno)
{
    #ifdef DEBUG
         cout << "\n***********DEBUG INFO**************\n"
                 "deleteRecord was called\n"
                 "parameter is uaccno (int): " << uaccno << "\n"
                 "***********************************\n\n";
    #endif

    struct record *temp;      
    struct record *prev;     
    int returnVal;

    if (start == NULL)      
    {
        cout << "The list is empty.\n";
        returnVal = -1;
    }

    else
    {
        prev = start;
        temp = prev->next;
        returnVal = -1;

        if (prev->accountno == uaccno)
        {
            start = temp;
            delete prev;
            prev = temp;    
            returnVal = 0;
        }

        else
        {          
            while (temp->next != NULL)
            {
                if (temp->accountno == uaccno)                  
                {
                    prev->next = temp->next;
                    delete temp;
                    temp = prev->next;
                    returnVal = 0;
                }

                else
                { 
                    prev = temp;
                    temp = temp->next;
                }
            }

            if (temp->accountno == uaccno)
            {
                prev->next = temp->next;
                delete temp;
                temp = prev->next;
                returnVal = 0;
            }
        }
    }

    return returnVal; 
}

/*****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   This function will read the records from a file into the list
//
//  Return values:  0 : success
//                 -1 : could not find read from the file
//               
****************************************************************/

int llist::readfile()
{
    #ifdef DEBUG
         cout << "\n***********DEBUG INFO**************\n"
                 "readfile was called\n"
                 "there are no parameters\n"
                 "***********************************\n\n";
    #endif

    ifstream myfile;
    int fnamelen;                
    struct record *temp;
    int accno;
    char name[25];
    char address[80];
    char var[80];
    char tempaddr[80];
    int loop;
    int returnVal;   

    accno = 0;
    name[0] = '\0';
    address[0] = '\0';
    var[0] = '\0',
    tempaddr[0] = '\0';

    temp = start;
    loop = 1;
    fnamelen = strlen(filename);

    if (filename[fnamelen - 4] == '.' &&
        filename[fnamelen - 3] == 't' &&
        filename[fnamelen - 2] == 'x' &&
        filename[fnamelen - 1] == 't')
    {
        myfile.open(filename);
    }

    if (myfile.is_open())
    {
        while (myfile.eof() == 0)
        {
            loop = 1;

            myfile >> accno;
            myfile.ignore(100, '\n');
            
            if (myfile.eof() == 0)
            {

                myfile.getline(name, 25);   

                while (loop == 1)
                {            

                    myfile.getline(var, 80);

                    if (var[strlen(var) - 1] == ';')
                    {
                        var[strlen(var) - 1] = '\0'; 
                        loop = 0;
                    }
 
                    strcat(tempaddr, var);
                }

                strcpy(address, tempaddr);

                addRecord(accno, name, address);
            }
        }

        myfile.close();
    }

    else
    {
        returnVal = -1;
    }

    return returnVal;
}

/*****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   This function will write the records from a list to a file
//
****************************************************************/

void llist::writefile()
{
    #ifdef DEBUG
         cout << "\n***********DEBUG INFO**************\n"
                 "writefile was called\n"    
                 "there are no parameters\n" 
                 "***********************************\n\n";       
    #endif
                
    ofstream myfile;
    int fnamelen;                 
    struct record *temp;           

    temp = start;                
    fnamelen = strlen(filename);

    if (filename[fnamelen - 4] == '.' &&
        filename[fnamelen - 3] == 't' &&                          
        filename[fnamelen - 2] == 'x' &&
        filename[fnamelen - 1] == 't')              
    {
        myfile.open(filename);

        while (temp != NULL)
        {
            myfile << temp->accountno << endl;
            myfile << temp->name << endl;
            myfile << temp->address << ";\n";

            temp = temp->next;
        }

        myfile.close();
    }

    else
    {
        cout << "**Error** Could not write to the file.";
    }
}

/*****************************************************************
//
//  Function name: cleanup  
//
//  DESCRIPTION:   This function releases all allocated space int the heap memory.
//
****************************************************************/

void llist::cleanup()
{
    #ifdef DEBUG
         cout << "\n***********DEBUG INFO**************\n"
                 "cleanup was called\n"    
                 "there are no parameters\n" 
                 "***********************************\n\n";       
    #endif
                
    struct record *temp;
    struct record *nextrec;

    temp = start;                
    nextrec = temp->next;

    while (temp != NULL)
    {
        delete temp;

        temp = nextrec;

        if (temp != NULL)
        {
            nextrec = temp->next;
        }
    }           
}

/*****************************************************************
//
//  Function name: reverse
//
//  DESCRIPTION:   This function calls the private reverse function.
//
****************************************************************/

void llist::reverse()
{
    start = reverse(start);
} 

/*****************************************************************
//
//  Function name: reverse           
//           
//  DESCRIPTION:   This function reverses the order of the list
//
//  Parameters:    temp (record *) : the start of the list
//           
//  Return values: returnVal : The new start of the list
//
****************************************************************/

record *llist::reverse(record *temp)
{
    #ifdef DEBUG
         cout << "\n***********DEBUG INFO**************\n"
                 "reverse was called\n"    
                 "parameter is temp (record *)\n" 
                 "***********************************\n\n";       
    #endif

    record *nextrec;
    record *returnVal;

    if (start->next != NULL)
    {
        nextrec = temp->next;

        if (nextrec->next != NULL)
        {
            returnVal = reverse(temp->next);
            nextrec->next = temp;
        
            if (temp->next == start->next)
            {
                temp->next = NULL;
            }
        }

        else
        {
            returnVal = temp->next;
            returnVal->next = temp;
            temp->next = NULL;
        }
    }

    else
    {
        returnVal = start;
    }
    
    return returnVal;
}
