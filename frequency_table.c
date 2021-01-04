#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Q1.h"

int main ( int argc, char *argv[] ) {
   char* flagOne = "-F";
   char *fileName = NULL;                              /* Originial File*/
   char *argument;
   int length;
   int j;
   int k;

   /* File pointers */
   FILE *firstFile;

   int* indvFreqTable;
   int i;
   char line[500];
   char* linePointer;

   int totalLetters = 0;
   int totalChars = 0;

   int *totalFreqTable = malloc (sizeof(int) * ALPHA_SIZE);

   for (i = 0; i < ALPHA_SIZE; i++) {
      totalFreqTable[i] = 0;
   }

   /*If flag argument exists, choose the argument that is one index over as the fulename */
   for (i = 0; i < argc; i++){
      if ((strcmp (argv[i], flagOne) == 0) && (argv[i+1] != NULL)){
         fileName = argv[i+1];
      }
   }

   /* If no space bw flag and filename, cycle through each argument and return the filename */
   if (fileName == NULL) {
      for (i = 0; i < argc ;i++) {
         argument = argv[i];
         length = strlen(argument);

         for (j = 0; j < length; j++){
            if ((argument[j] == '-') && (argument[j+1] == 'F')) {
               for (k = 0; k < length -2; k++) {
                  argument[k] = argument[k+2];
               }
               argument[k] = '\0';
               fileName = argument;    
            }
         }
      } 
   }

   /* If input file exists, calculate summary table */
   if (fileName != NULL) {
      if ( (firstFile = fopen(fileName, "r")) != NULL ) {
         while ( fgets ( line, 500, firstFile ) != NULL ) {
            linePointer = malloc (sizeof(char) * strlen(line));
            strcpy(linePointer, line);

            indvFreqTable = frequency_table(linePointer);

            for (i = 0; i < ALPHA_SIZE; i++) { 
               totalFreqTable[i] += indvFreqTable[i];
            }
      
            free (indvFreqTable);

            totalLetters += letter_count(linePointer);
            totalChars += strlen(linePointer) - 1;  

            free (linePointer);

            printf("%s\n", line);
         }
         printf ("Number of letters in the text = %d \t Number of characters in the text = %d\n", totalLetters, totalChars);
         printf ("Letter \t Frequency\n");
      
         for (i = 0; i < ALPHA_SIZE; i++) {
            printf ("[%c] \t %d\n", i + ASCII_LETTER - CAPITAL_DIFFERENCE, totalFreqTable[i]);
         }

         free (totalFreqTable);
      } else {
         printf ( "Cannot open file. \n" );
      }

      fclose (firstFile);
  }

  /*If there are no command line arguments or the input file doesn't exist, read from stdin*/
   if ((argc == 1) || (fileName == NULL)) {
      printf ("Enter \"d\" to exit.\n");
      while ( fgets ( line, 500, stdin ) != NULL ) {

         /* User must enter the single letter d to exit stdin */
         if ((line[0] == 'd') && (strlen(line) < 3)){
            break;
         }

	      linePointer = malloc (sizeof(char) * strlen(line));
	      strcpy(linePointer, line);

         indvFreqTable = frequency_table(linePointer);

         for (i = 0; i < ALPHA_SIZE; i++) { 
            totalFreqTable[i] += indvFreqTable[i];
         }
   
	      free (indvFreqTable);

         totalLetters += letter_count(linePointer);
         totalChars += strlen(linePointer) - 1;	 

	      free (linePointer);
      }
   

      printf ("Number of letters in the text = %d \t Number of characters in the text = %d\n", totalLetters, totalChars);
      printf ("Letter \t Frequency\n");
   
      for (i = 0; i < ALPHA_SIZE; i++) {
         printf ("[%c] \t %d\n", i + ASCII_LETTER - CAPITAL_DIFFERENCE, totalFreqTable[i]);
      }

      free (totalFreqTable);
   }

   return (0);
}
