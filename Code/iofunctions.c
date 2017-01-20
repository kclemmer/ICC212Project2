/**************************************************************************************
//
// Name: Kenji Clemmer
// 
// Homework: Project1
//
// Class: ICS 212
//
// Instructor: Ravi Naryan
//
// Date: 22 Oct 2016
//
// File: iofunctions.c
//
// Description: These are the input and output file functions
//
//*************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "record.h"

extern int debug;

void readfile(struct record**, char[]);
void writefile(struct record *, char filename[]);

/**************************************************************************************
//
// Function Name: readfile
//
// Description: reads in files to the program, maximum array size is 5 so if the 
//              read in input is greater than five accounts, it ceases to allow 
//              further information. 
//
// Parameters: account (struct record[])
//             pnumAccounts (int*)
//             filename (char[])
//
// Return Values: n/a
//
//*************************************************************************************/

void readfile(struct record ** head, char filename[])
{
   int actNo = 0;
   int age = 0;
   char mellamo[25];
   char home[80];
   int len = 0;
   int i = 0;
   int place = 1;
   char input[100];

   if(debug==1)
   {
      printf("\n---\nThis is Debug for readfile:\n");
      printf("Struct Record: %x\nFilename: %s\n---\n", head, filename);
   }   

   if( access(filename, F_OK) != -1)
   {  
      FILE * reader = fopen(filename, "r");  
      fgets(input, 100, reader);

      while(!feof(reader))
      {  
         switch(place)
         {
            case 1:
               actNo = atoi(input);         
               place = 2;
               break;
            case 2:
               strcpy(mellamo, input);
               place = 3;
               break;
            case 3:
               strcpy(home, input);
               len = strlen(input);
               home[len]='\0';
               if (input[len-2] == '!')
               {
                  len = strlen(home);
                  home[len-2]='\0';
                  place = 5;
               }
               else
               {
                  place = 4;
               }
               break;
            case 4:
               len = strlen(input);
               input[len]='\0';
               strcat(home, input);          
               if (input[len-2]=='!')
               { 
                  len = strlen(home);
                  home[len-2]='\0';
                  place = 5;
               }
               break;
            case 5:
               age = atoi(input);
               addRecord(head, actNo, mellamo, home, age);
               for(i=0; i<25; i++)
               { 
                  mellamo[i] = '\0';
               }
               for(i=0; i<80; i++)
               { 
                  home[i] = '\0';
               }
               place = 1;
               break;
            default:
               break;
         }
         fgets(input,100,reader);      
      }


      fclose(reader);
   }
   else
   {
      printf("Database not available yet");
   }

}


/**************************************************************************************
//
// Function Name: writefile
//
// Description: writes the accounts to an output file
//
// Parameters: accounts (struct record[])
//             numAccounts (int)
//             filename (char[])
//
// Return Values: n/a
// 
//*************************************************************************************/

void writefile(struct record* accounts, char filename[])
{
   struct record * temp;
   temp = accounts;
   FILE * outer;

   if(debug==1)
   {
      printf("\n---\nThis is Debug for writefile:\nStruct Record: %x\nFilename: %s\n---\n", accounts, filename);
   }

   if(temp == NULL)
   { 
      outer = fopen(filename, "w");
      fclose(outer);
   }
   else
   {
      outer = fopen(filename, "w");

      while(temp != NULL)
      {
         fprintf(outer,"%d\n",temp->accountno);
         fprintf(outer,"%s",temp->name);
         fprintf(outer,"%s!\n",temp->address);
         fprintf(outer,"%d\n",temp->yearofbirth);
         temp = temp->next; 
      }
   fclose(outer); 
   }   
}
