#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "Q2.h"

int main ( int argc, char *argv[] ) {
   /* Flag arguments */
   char *flagOne = "-F";                  /* Name of Input File. If missing, print from stdin */
   char *flagTwo = "-O";                  /* Name of Output File. If missing, print decoded text to stdout */
   char *flagThree = "-n";                /* Supresses the printing of the code to stdout */
   char *flagFour = "-s";                 /* Prints the shiftNumber to stdout */
   char *flagFive = "-S";                 /* */
   char *flagSix = "-t";                  /* */
   char *flagSeven = "-x";                /* */

   /* File pointers*/
   FILE *firstFile;
   FILE *secondFile;

   /* File manipulation */
   char *inputFileName = NULL;  
   char *outputFileName = NULL;                    
   char line[MAX_SIZE];                                /* Stores lines from input file/stdin one at a time*/
   char *linePointer;                                  /* Points to the stored line that is returned from fgets */

  /* Indices */
   int i; 
   int j;
   int stdinLength = 0;
   int tempStdinLength = 0;
   String *copy;


   /* ChiShift Function */
   int correctShift;

   /* Letter Frequency vairables and arrays*/
   int totalLetters = 0;
   int totalChars = 0;
   int *text_freq = create_freq_table();

   String *head = NULL;
   int bool = 0;
   int supressPrint;
   int printDecodeShift;
   int printEncodeShift;
   int printTableSummary;
   int printChiValues;

   /* Responses to flag arguments */
   inputFileName = fileNameArgument (argc,argv,flagOne);
   outputFileName = fileNameArgument (argc,argv,flagTwo);
   supressPrint = flagArgument (argc,argv,flagThree);
   printDecodeShift = flagArgument (argc,argv,flagFour);
   printEncodeShift = flagArgument (argc,argv,flagFive);
   printTableSummary = flagArgument (argc,argv,flagSix);
   printChiValues = flagArgument (argc,argv,flagSeven);
   
   /* If input file exists, read in the file*/ 
   if (inputFileName != NULL) {
      if ( (firstFile = fopen(inputFileName, "r")) != NULL ) {
         while ( fgets ( line, MAX_SIZE, firstFile ) != NULL ) {
            linePointer = malloc (sizeof(char) * strlen(line));
            strcpy(linePointer, line);
            add_letters (text_freq,linePointer);
            totalLetters += letter_count(linePointer);
            totalChars += strlen(linePointer) - 1; 
            free (linePointer);
         }

         correctShift = encode_shift (totalLetters, text_freq);         /* Finds encoded shift using chi square formula */

         /* Prints out shifts is user requests to*/
	      if (printDecodeShift == SUCCESS) {
	         printf ("\n");
            printf ("Decode Shift = %d\n", correctShift * -1);
	      }
	 
	      if (printEncodeShift == SUCCESS) {
	         printf ("\n");
	         printf ("Encode Shift = %d\n", correctShift);
	      }

         /* Prints out summary table for chi values */
         if (printChiValues == SUCCESS) {
            printf ("\n");
            print_chi_values (totalLetters, text_freq);
         }

         /* Prints out summary table for letter frequency */
	      if (printTableSummary == SUCCESS) {
            printf ("\n");
	         print_table (text_freq, totalLetters, totalChars);
         }

         free (text_freq);
         
      } else {
         printf ( "Cannot open file. \n" );
      }

      fclose (firstFile);

      /* If output file exists, write input to output file*/
      if (outputFileName != NULL) {
         firstFile = fopen(inputFileName, "r");
         secondFile = fopen(outputFileName, "w");

         while ( fgets ( line, MAX_SIZE, firstFile ) != NULL ) {
            linePointer = malloc (sizeof(char) * strlen(line));
            strcpy(linePointer, line);
            fprintf (secondFile, "%s\n", decode_text (linePointer, correctShift));
            free (linePointer);
         }

         fclose (firstFile);
         fclose (secondFile);

      /* If output file doesn't exists, write to stdout */   
      } else {
         firstFile = fopen(inputFileName, "r");
         if (supressPrint == FAILURE) {
            printf("\n");
            while ( fgets ( line, MAX_SIZE, firstFile ) != NULL ) {
               linePointer = malloc (sizeof(char) * strlen(line));
               strcpy(linePointer, line);
               printf ("%s\n", decode_text (linePointer, correctShift));
               free (linePointer);
            }
	      }

         fclose (firstFile);
      }
   }

   /* If user enters no command line arguments or no input file is recognized, receive input from stdin */
   if ((argc == 1) || (inputFileName == NULL)) {

      /* User must enter the single letter d to exit stdin */
      printf ("Enter \"⌃d\" to insert EOF character.\n");
      while ( fgets ( line, MAX_SIZE, stdin ) != NULL ) {

         /* If user enters nothing in stdin, quit program */
         if ((line[0] == 'd') && (strlen(line)<3) && (stdinLength == 0)) {
            return (0);
	      }

         /* User must enter the single letter d to exit stdin */
         if ((line[0] == 'd') && (strlen(line) < 3)){
            break;
         }

	      linePointer = malloc (sizeof(char) * strlen(line));
	      strcpy(linePointer, line);
         add_letters (text_freq,linePointer);

         totalLetters += letter_count(linePointer);
         totalChars += strlen(linePointer) - 1;	 

         head = add_front (head, linePointer, bool);
	      bool++;

	      free (linePointer);
	      stdinLength++;
      }

      correctShift = encode_shift (totalLetters, text_freq);      /* Finds encoded shift using chi square formula */

      /* Prints out shifts is user requests to*/
      if (printDecodeShift == SUCCESS) {
	      printf ("\n");
         printf ("Decode Shift = %d\n", correctShift);
      }

      if (printEncodeShift == SUCCESS) {
	      printf ("\n");
	      printf ("Encode Shift = %d\n", correctShift * -1);
      }

       /* Prints out summary table for chi values */
      if (printChiValues == SUCCESS) {
         printf ("\n");
         print_chi_values (totalLetters, text_freq);
      }

      /* Prints out summary table for letter frequency */
      if (printTableSummary == SUCCESS) {
         printf ("\n");
	      print_table(text_freq, totalLetters, totalChars);
      }

      /* If output file exists, write stdin to output file*/
      if (outputFileName != NULL) {
         secondFile = fopen(outputFileName, "w");
	      copy = head;
	      tempStdinLength = stdinLength;

         for (i = 0; i < stdinLength - 1; i++){
            while ((head != NULL) && (head->next != NULL) && (j < tempStdinLength - 1)){
               head = head->next;
	            j++;
            }
          
            fprintf (secondFile,"%s\n", decode_text(head->value,correctShift));
	         head = copy;
	         tempStdinLength--;
	         j = 0;
	      }

	      fprintf (secondFile, "%s\n", decode_text(head->value,correctShift));
         fclose (secondFile);

      /* If output file doesn't exists, write to stdout */ 
      } else {
         if (supressPrint == FAILURE) {
	         printf ("\n");
            print_decoded_list (head, correctShift, stdinLength);
         }  
      }
      free_list(head); 
      free (text_freq);
   }

   return (0);
}
