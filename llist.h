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
//  FILE:        llist.h
//
//  DESCRIPTION:
//   This file contains the class llist with methods for Project 2
//
****************************************************************/

#ifndef LLIST_H
#define LLIST_H

#include <iostream>

using std::ostream;

class llist
{
  private:
    record *    start;
    char        filename[16];
    int         readfile();
    void        writefile();
    record *    reverse(record * );
    void        cleanup();

  public:
    llist();
    llist(char[]);
    ~llist();
    int addRecord (int, char [ ],char [ ]);
    int printRecord (int);
    friend ostream& operator<<(ostream& os, llist& mylist);
    int findRecords (char [ ]);
    int deleteRecord(int);
    void reverse();
};

#endif
