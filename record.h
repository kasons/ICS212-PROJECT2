/*****************************************************************
//
//  NAME:        Kason Shiroma
//
//  HOMEWORK:    project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        April 12, 2019
//
//  FILE:        record.h
//
//  DESCRIPTION:
//   This file contains the record structure for project2 -
//    The Bank Database Application
//
****************************************************************/

#ifndef RECORD_H
#define RECORD_H

struct record
{
    int                accountno;
    char               name[25];
    char               address[80];
    struct record*     next;
};

#endif
