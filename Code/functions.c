/********************************************************************************************************
// 
// Name: Kenji Clemmer
// 
// Homework: Project1
//
// Class: ICS 212
//  
// Instructor: Ravi Narayan
//
// Date: 22 Oct 2016
// 
// File: functions.c
//
// Description: This file contains all of the functions for the program except the getAddress function
//
//*******************************************************************************************************/

#include<stdlib.h>
#include "record.h"
#include "menu.h"

extern int debug;

/********************************************************************************************************
// 
// Function name: addRecord
//
// Description: Adds a record into the list, and sorts them records according to their yearofbirth, in 
//              the event of two records sharing a year of birth, the record currently being added will
//              be placed in front of the record currently on the stack.
//
// Parameters: record (struct record**)
//             accountNo (int)
//             name (char[])
//             address (char[])
//             year (int)
//
// Return values: 0: success
//               -1: the value was not found
//
//*******************************************************************************************************/

int addRecord(struct record ** head, int accountNumber, char nameOf[], char addressOf[], int year) 
{
   struct record * temp1;
   struct record * temp2;
   struct record * temp3;
   int inserted = 0;

   if (debug==1)
   {
      printf("\n--\nThis is Debug for addRecord: \n");
      printf("Struct Record: %x\nAccountNumber: %d\nName: %s\nAddress: %s\n", head, accountNumber, nameOf, addressOf);
      printf("Date of Birth: %d\n--\n", year);
   }   

   temp2 = *head;
   temp3 = *head;

   temp1 = (struct record*)malloc(sizeof(struct record));
   temp1->accountno = accountNumber;
   strcpy(temp1->name, nameOf);
   strcpy(temp1->address, addressOf);
   temp1->yearofbirth = year;   
   temp1->next = NULL;

   if (temp2 == NULL)
   {
      *head = temp1;
   }
   else
   { 
      if(temp1->yearofbirth >= temp2->yearofbirth)
      {
         temp1->next = temp2;
         *head = temp1;         
      }
      else
      {
         while(temp2->next != NULL && inserted == 0)
         {
            temp2 = temp2->next;

            if(temp1->yearofbirth == temp2->yearofbirth)
            {  
               inserted = 1;
               temp1->next = temp2;
               temp3->next = temp1;
            }
            else
            {
               temp3 = temp3->next;
            }      
         }
         if(temp2->next == NULL && inserted == 0)
         {
            temp2->next = temp1;        
         }
      }
   }
} 

/*******************************************************************************************************
//
// Function name: printRecord
//
// Description: prints the record(s) matching the given account number
//
// Parameters: record (struct record*)
//             num (int)
//
// Return values: 0: success
//                1: the list is empty
//                2: the record was not found
//
//******************************************************************************************************/

int printRecord(struct record * record, int num) 
{
   struct record * temp1;
   int found = 2;

   if(debug==1)
   {
      printf("\n--\nThis is Debug for printRecord: \n");
      printf("Struct Record: %x\nAccountNumber: %d\n--\n",record,num);
   }

   temp1 = record;

   if(temp1 == NULL)
   {
      found = 1;
   }   
   
   while(temp1 != NULL)
   {
      if(temp1->accountno == num)
      {   
         found = 0;
         printf("Account Number: %d\n", temp1->accountno);
         printf("Name: %s", temp1->name);
         printf("Address:\n%s\n", temp1->address);
         printf("Year of Birth: %d\n\n", temp1->yearofbirth);
      }
   temp1 = temp1->next;
   }   
   return found;
}

/******************************************************************************************************
//
// Function name: modifyRecord
//
// Description: modifies the address for the record(s) matching the given account number
//
// Parameters: record (struct record*)
//             num (int)
//             address (char [])
// 
// Return values: 0: success
//                1: the list is empty
//                2: the record was not found
//
//*****************************************************************************************************/

int modifyRecord(struct record * record, int num, char add[]) 
{
   struct record * temp1;
   int recordStatus = 2;

   if(debug==1)
   {
      printf("\n---\nThis is Debug for modifyRecord: \n");
      printf("Struct Record: %x\nAccountNumber: %d\nAddress: %s\n---\n", record, num, add);
   }
   
   temp1 = record;

   if(temp1 == NULL)
   {
      recordStatus = 1;
   }
   while(temp1 != NULL)
   {
      if(temp1->accountno == num)
      {
         strcpy(temp1->address, add);
         recordStatus = 0;
      }
   temp1 = temp1->next;
   }
   return recordStatus;
}

/*****************************************************************************************************
// 
// Function name: printAllRecords
// 
// Description: prints all of the records in the list
//
// Parameters: record (struct record*)
//
// Return values: n/a
//
//****************************************************************************************************/

void printAllRecords(struct record * record) 
{
   struct record * temp;
   temp = record;

   if(debug==1)
   {
      printf("\n--\nThis is debug for printAllRecords: \n");
      printf("Struct Record: %x\n--\n",record);
   }

   if(temp == NULL)
   {
      printf("The list is empty");
   }

   while(temp != NULL)
   {
      printf("Account Number: %d\n", temp->accountno);
      printf("Name: %s", temp->name );
      printf("Address:\n%s\n", temp->address);
      printf("Year of Birth: %d\n\n", temp->yearofbirth);
      temp = temp->next;
   }
}

/****************************************************************************************************
//
// Function name: deleteRecord
// 
// Description: deletes the record(s) matching the given account number
//
// Parameters: record (struct record**)
//             accountNo (int)
//
// Return values: 0: success
//                1: the list is empty
//                2: the record was not found
//
//***************************************************************************************************/

int deleteRecord(struct record ** head, int num)
{
   struct record * current = NULL;
   struct record * prev = NULL;
   struct record * headAccess = *head;

   int status = 2;

   if(debug==1)
   {
      printf("\n---\nThis is debug for deleteRecord");
      printf("Struct Record: %x\n Account Number: %d\n---\n", head, num);
   }

   if(*head == NULL)
   {
      status = 1;
   }
   else
   {
      if(headAccess->next == NULL)
      {
         if(headAccess->accountno == num)
         {
            status = 0;
            free(*head);
            *head = NULL;
         }
      }
      else
      {
         current = *head;   
         while(current != NULL)
         {           
            if(current->accountno == num)
            {
               if (prev != NULL)
               {
                  status = 0;
                  prev->next = current->next;
                  free(current);
                  current = prev->next;
               }
               else
               {
                  status = 0;
                  *head = current->next;
                  free(current);
                  current = *head;
               }
            }
            else
            {
               prev = current;
               current = current->next;
            }
           
         }
      }
   }
   return status;
}

