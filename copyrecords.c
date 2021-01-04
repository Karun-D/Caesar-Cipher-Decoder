#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "Q2.h"
#include "Q3.h"

int main ( int argc, char *argv[] ) {
   /* Flag arguments */
   char *flagOne = "-F";                  /* Name of Input File. If missing, print from stdin */
   char *flagTwo = "-O";                  /* Name of Output File. If missing, print decoded text to stdout */
   char *flagThree = "-D";                /* Used to find the shift to encode records */
   char *flagFour = "-r";                 /* Prints records in reverse */

   /* File pointers*/
   FILE *firstFile;
   FILE *thirdFile;
   FILE *fourthFile;

   /* File manipulation */
   char *inputFileName = NULL;  
   char *outputFileName = NULL;  
   char *textFileName = NULL;  
   int printReverse; 

   char line[MAX_SIZE];                                /* Stores lines from input file/stdin one at a time*/
   char *linePointer;                                  /* Points to the stored line that is returned from fgets */

   /* Letter Frequency vairables and arrays*/
   int totalLetters = 0;
   int *text_freq;

   /* ChiShift Function */
   int correctShift;

   inputFileName = fileNameArgument (argc,argv,flagOne);
   outputFileName = fileNameArgument (argc,argv,flagTwo);
   textFileName = fileNameArgument (argc,argv,flagThree);
   printReverse = flagArgument (argc,argv,flagFour);

   /* Calculates the Caesar cipher shift to be used to decode the text fields of each record via the text file */ 
   if (textFileName != NULL) {
      if ( (firstFile = fopen(textFileName, "r")) != NULL ) {
         text_freq = create_freq_table();
         while ( fgets ( line, MAX_SIZE, firstFile ) != NULL ) {
            linePointer = malloc (sizeof(char) * strlen(line));
            strcpy(linePointer, line);
            add_letters (text_freq,linePointer);
            totalLetters += letter_count(linePointer);
            free (linePointer);
         }

         correctShift = encode_shift (totalLetters, text_freq);

         free (text_freq);
      } else {
         printf ( "Cannot open file. \n" );
      }

      fclose (firstFile);

   } else {
      correctShift = 0;
   }

   if (inputFileName != NULL) {

      if ( (thirdFile = fopen(inputFileName, "rb")) != NULL ) {
         int structExists;
	      int numOfRecords = 0;
	      Record * head = NULL; 

         while (1) {
	         tempRecord * temp = malloc (sizeof(tempRecord));
            structExists = fread(temp, sizeof(tempRecord), 1, thirdFile);
            if (structExists == 0){
		         free (temp);
               break;
	         }

            if (textFileName != NULL) {
               strcpy (temp->stringOne, decode_text (temp->stringOne, correctShift));
               strcpy (temp->stringTwo, decode_text (temp->stringTwo, correctShift));
            }

	         head = add_record (head,temp);

            free (temp);
	         numOfRecords++;

	       }

          fclose (thirdFile);

          if (outputFileName != NULL) {
	          
            if ( (fourthFile = fopen(outputFileName, "wb")) != NULL ) {
   /*            write_all_records (head, numOfRecords, fourthFile); */
               if (printReverse == SUCCESS) {
                  write_reverse(head, fourthFile);
               } else {
                  write_all_records (head,numOfRecords, fourthFile);
	            }
               free_records (head);
               fclose (fourthFile);
            } else {
               printf ( "Cannot open file. \n" );
            }

          } else {
 /*            print_all_records (head, numOfRecords);  */
            if (printReverse == SUCCESS) {
	       print_reverse(head);
            } else {
               print_all_records (head,numOfRecords);
	         }
            free_records (head);
          }

      }
        
   } else {
      printf ( "Cannot open file. \n" );
   }
   
   return (0);
}
