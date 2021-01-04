/*ALL documentation in associated .h file*/

#include "Q1.h"

int letter_count ( char * str ) {
   int i = 0;                           /* Index variable */
   int length = 0;                      /* Int variable that stores the number of letters in a string */

   /* Cycles through string */
   while (str[i] != '\0'){
      /* If character is a letter, length variable is incremented */
      if (((str[i] >= ASCII_LETTER) && (str[i] <= ASCII_LETTER + ALPHA_SIZE)) || ((str[i] >= ASCII_LETTER - CAPITAL_DIFFERENCE) && (str[i] <= ASCII_LETTER + ALPHA_SIZE - CAPITAL_DIFFERENCE))){
         length++;
      }
      i++;
   }

   return length;
}

int * frequency_table ( char * str ) {
   int *freqTable = malloc (sizeof(int) * ALPHA_SIZE);                  /* Allocate memory for an int array that is the size of the alphabet */
   /* Index variables */
   int i = 0;
   int j = 0;
   int asciiLetter = ASCII_LETTER;                                      /* Index variable that represents each letter of the alphabet in ASCII form */
   int length = strlen(str);

   /* Cycles through alphabet */
   for (i = 0; i < ALPHA_SIZE; i++) {
      /* Initializes each index */
      freqTable[i] = 0;
      for (j = 0; j < length; j++){
         /* If the character is the current letter in the array index, increment the frequency */
         if ((str[j] == asciiLetter) || (str[j] == (asciiLetter - CAPITAL_DIFFERENCE))){
            freqTable[i]++;
         }
      }
      asciiLetter++;
   }

   return freqTable;
}
