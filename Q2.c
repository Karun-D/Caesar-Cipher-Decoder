/*ALL documentation in associated .h file*/

#include "Q2.h"

char * fileNameArgument (int argc, char *argv[], char* flag) {
   char *fileName = NULL;        /* Name of file to be returned */
   char *argument;               /* Used to temporarily store each command line argument */
   int argumentLength;           /* Used to cycle through command line argument */
   /* index Variables */
   int i;
   int j;
   int k;

   /* If flag argument is found, the filename is selected at the next index */
   for (i = 0; i < argc; i++){
      if ((strcmp (argv[i], flag) == 0) && (argv[i+1] != NULL)){
         fileName = argv[i+1];
         return fileName;
      }
   }

   /**
    * If the flag argument is not found, function will iterate over each command line arg 
    * to find any flag argument with no spaces
    */
   if (fileName == NULL) {
      /* Cycles through command line arguments */
      for (i = 0; i < argc; i++) {
         /* Temporarily stores command line argument */
         argument = argv[i];
         argumentLength = strlen(argument);
         /* Cycles through command line argument */
         for (j = 0; j < argumentLength; j++){
            /* If the flag is found without a space in the argument, the rest of the string is returned */
            if ((argument[j] == flag[0]) && (argument[j+1] == flag[1]) && (argv[j+1] != NULL)) {
               /* Stores the filename in the variable "argument" */
               for (k = 0; k < argumentLength - 2; k++) {
                  argument[k] = argument[k+2];
               }
               argument[k] = '\0';
               /* Assigns the filename string to its respective variable, and returns it */
               fileName = argument;  
               return fileName;  
            }
         }
      } 
   }

   return fileName;
}

int flagArgument (int argc, char *argv[], char* flag) {
   char *argument;
   int argumentLength;
   int i;
   int j;
   int argumentFound = FAILURE;

   /* If flag argument is found, the function returns "SUCCESS" to trigger a response in the program */
   for (i = 0; i < argc; i++){
      if ((strcmp (argv[i], flag) == 0) && (argv[i+1] != NULL)){
         return SUCCESS;
      }
   }

   /**
    * If the flag argument is not found, function will iterate over each command line arg 
    * to find any flag argument with no spaces (ex. "-Ftext_name.txt")
    */
   if (argumentFound == FAILURE) {
      /* Cycles through command line arguments */
      for (i = 0; i < argc; i++) {
         /* Temporarily stores command line argument */
         argument = argv[i];
         argumentLength = strlen(argument);
         /* Cycles through command line argument */
         for (j = 0; j < argumentLength; j++){
            /* If flag argument is found with no spaces, the function returns "SUCCESS" to trigger a response in the program */
            if ((argument[j] == flag[0]) && (argument[j+1] == flag[1])) {
               return SUCCESS; 
            }
         }
      } 
   }

   /**
    * If the flag argument is not found, function will iterate over each command line arg 
    * to find any flag arguments that are grouped together (ex. "-stx")
    */
   if (argumentFound == FAILURE) {
      /* Cycles through command line arguments */
      for (i = 0; i < argc; i++) {
         /* Temporarily stores command line argument */
         argument = argv[i];
         argumentLength = strlen(argument);
         /* Cycles through command line argument */
         for (j = 0; j < argumentLength; j++){
            /* If flag argument is grouped, the function returns "SUCCESS" to trigger a response in the program */
            if ((argument[0] == flag[0]) && (argument[j] == flag[1]) ) {
               return SUCCESS; 
            }
         }
      } 
   }

   return FAILURE;
}

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

int * create_freq_table () {
   int *freq_table = malloc (sizeof(int) * ALPHA_SIZE);        /* Allocates memory for an int array that is the size of the alphabet */
   int i;                                                      /* index variable */

   /* Initializes array */
   for (i = 0; i < ALPHA_SIZE; i++) {
      freq_table[i] = 0;
   }
   return freq_table;
}

void add_letters(int *freq_table, char *string) {
   int length = strlen(string);                                /* Used to iterate over string */
   /* Index variables */
   int i;
   int j;

   /* Cycles through alphabet */
   for (i = 0; i < ALPHA_SIZE; i++) { 
      /* Cycles through input string */
      for (j = 0; j < length; j++){
         /* If the character in the string is the current letter in the alphabet array index, increment the frequency */
         if ((string[j] == (i + ASCII_LETTER)) || (string[j] == ((i + ASCII_LETTER) - CAPITAL_DIFFERENCE))){
            freq_table[i]++;
         }
      } 
   } 
}


int offset (char letter) {
   /* Return an integer representing the letter's index in an alphabet array */
   if ((letter >= ASCII_LETTER) && (letter <= ASCII_LETTER + ALPHA_SIZE)) {
      return (((int) letter) - ASCII_LETTER);
   } else if  ((letter >= ASCII_LETTER - CAPITAL_DIFFERENCE) && (letter <= ASCII_LETTER + ALPHA_SIZE - CAPITAL_DIFFERENCE)) {
      return (((int) letter) - ASCII_LETTER - CAPITAL_DIFFERENCE);
   } else {
      return -1;
   }
}

char encode (char letter, int shiftNumber) {
   if (shiftNumber == 0) {
      return letter;       
   } 

   if (shiftNumber > 0) {
      /* If the current character is a lower case letter */
      if ((letter >= ASCII_LETTER ) && (letter <= ASCII_LETTER + ALPHA_SIZE)) {
         /* If applying the encryption converts the letter to a value less than z ... */
         if (letter < ASCII_LETTER + ALPHA_SIZE - shiftNumber) {
            /* ... apply encrpytion */
            letter += shiftNumber;
            return letter;
         /* If applying the encryption converts the letter to a value greater than z ... */
         } else {
            /* ... carry over the remainder starting at the letter "a" and apply the encryption */
            letter = ((letter + shiftNumber) % (ASCII_LETTER + ALPHA_SIZE) ) + ASCII_LETTER;
            return letter;
         }
      }
        
      /* If the current character is an uppper case letter */       
      if ((letter >= ASCII_LETTER - CAPITAL_DIFFERENCE) && (letter <= ASCII_LETTER - CAPITAL_DIFFERENCE + ALPHA_SIZE)) {          
         /* If applying the encryption converts the letter to a value less than Z ... */
         if (letter < ASCII_LETTER - CAPITAL_DIFFERENCE + ALPHA_SIZE -shiftNumber) {
            /* ... apply encrpytion */
            letter += shiftNumber;
            return letter;
         /* If applying the encryption converts the letter to a value greater than Z ... */
         } else {
            /* ... carry over the remainder starting at the letter "A" and apply the encryption */
            letter = ((letter + shiftNumber) % (ASCII_LETTER - CAPITAL_DIFFERENCE + ALPHA_SIZE) + (ASCII_LETTER - CAPITAL_DIFFERENCE));
            return letter;
         }
      }
   }   
            

   if (shiftNumber < 0) {
      /* If the current character is a lower case letter */
      if ((letter >= ASCII_LETTER ) && (letter <= ASCII_LETTER + ALPHA_SIZE)) {
         /* If applying the encryption converts the letter to a value greater than a ... */
         if (letter > ASCII_LETTER - shiftNumber) {
            /* ... apply encrpytion */
            letter += shiftNumber;
            return letter;
         /* If applying the encryption converts the letter to a value less than a ... */
         } else {
            /* ... carry over the remainder starting at the letter "z" and apply the encryption */
            letter = (ASCII_LETTER + ALPHA_SIZE) - ((ASCII_LETTER ) - (letter + shiftNumber));
            return letter;
         }
      }

      /* If the current character is an upper case letter */
      if ((letter >= ASCII_LETTER - CAPITAL_DIFFERENCE) && (letter <= ASCII_LETTER - CAPITAL_DIFFERENCE + ALPHA_SIZE)) {          
         /* If applying the encryption converts the letter to a value greater than A ... */
         if (letter > ASCII_LETTER - CAPITAL_DIFFERENCE -shiftNumber) {
            /* ... apply encrpytion */
            letter += shiftNumber;
            return letter;
         /* If applying the encryption converts the letter to a value less than A ... */
         } else {
            /* ... carry over the remainder starting at the letter "Z" and apply the encryption */
            letter = (ASCII_LETTER - CAPITAL_DIFFERENCE + ALPHA_SIZE) - ((ASCII_LETTER - CAPITAL_DIFFERENCE) - (letter + shiftNumber));
            return letter;
         }
      }
   }

   return (1);
}

int encode_shift (int totalLetters, int *text_freq){
   int i;         /* Index variable */       

   /* letter frequencies that are commonly found in the English language ([i] = 0 -> A, [i] = 25 -> Z)*/
   double EF [] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07707, 0.01929,
   0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.0236, 0.0015, 0.01974, 0.00074}; 

   double chiSquaredNumerator;                           /* Calculates numerator of Chi Squared Formula */
   double tempChiResult = 0;                             /* Stores the Chi Result for each shift */
   double smallestChiResult = MAX_CHI_RESULT;                    /* Stores the lowest Chi Results calculated from all shifts */
   
   int shiftNumber;                                      /* Tests each potential shift number as input for chi squared formula, increments from 0 to 25 */
   int correctShift;                                     /* Stores the most accurate shift number (lowest Chi Results calculated from all shifts tested */

   /* Tests each possible shift number used to encrypt text */
   for (shiftNumber = 0; shiftNumber < ALPHA_SIZE; shiftNumber++){
      /* Cycles through alphabet */
      for (i = 0; i < ALPHA_SIZE; i++) {
         /* Performs Chi-Squared formula calculation */
         chiSquaredNumerator = (totalLetters * EF[offset((char)(i + ASCII_LETTER))] - text_freq[offset(encode(i + ASCII_LETTER,shiftNumber))]);
         chiSquaredNumerator *= chiSquaredNumerator;
         tempChiResult += chiSquaredNumerator  / (totalLetters * totalLetters * EF[offset((char)(i + ASCII_LETTER))]);
      }

      /* If the current result from the Chi-Squared formula is less than the smallestChiResult... */
      if (tempChiResult < smallestChiResult) {
         /* ...update the smallestChiResult and correct shift values */
         smallestChiResult = tempChiResult;
         correctShift = shiftNumber;
      }

      /* Resets temporary variable */
      tempChiResult = 0;
   }

   /* If the smalles result from the Chi-Squared formula is too large, the text is not encrypted */
   if (smallestChiResult > 0.5) {
      correctShift = 0;
   }

   return correctShift;
}

char* decode_text (char *line, int shiftNumber) {
   int i;                              /* Index variable */
   int length = strlen (line);         /* Used to iterate over input string */

   /* Cycles through input string */
   for (i = 0; i < length; i++) {
      /* Applies decryption */
      if (shiftNumber == 0) {
         line[i] += shiftNumber;
      }

      if (shiftNumber > 0) {
         /* If the current character is a lower case letter */
         if ((line[i] >= ASCII_LETTER ) && (line[i] <= ASCII_LETTER + ALPHA_SIZE)) {
            /* If applying the decryption converts the letter to a value greater than a ... */
            if (line[i] >= ASCII_LETTER + shiftNumber) {
               /* ... apply decryption */
               line[i] -= shiftNumber;
            /* If applying the decryption converts the letter to a value less than a ... */
            } else {
               /* ... carry over the remainder starting at the letter "z" and apply the decryption */
               line[i] = (ASCII_LETTER + ALPHA_SIZE) - ((ASCII_LETTER ) - (line[i] - shiftNumber));
            }
         }

         /* If the current character is an upper case letter */
         if ((line[i] >= ASCII_LETTER - CAPITAL_DIFFERENCE) && (line[i] <= ASCII_LETTER - CAPITAL_DIFFERENCE + ALPHA_SIZE)) {          
            /* If applying the decryption converts the letter to a value greater than A ... */
            if (line[i] >= ASCII_LETTER - CAPITAL_DIFFERENCE + shiftNumber) {
               /* ... apply decryption */
               line[i] -= shiftNumber;
            /* If applying the decryption converts the letter to a value less than A ... */
            } else {
               /* ... carry over the remainder starting at the letter "Z" and apply the decryption */
               line[i] = (ASCII_LETTER - CAPITAL_DIFFERENCE + ALPHA_SIZE) - ((ASCII_LETTER - CAPITAL_DIFFERENCE) - (line[i] - shiftNumber));
            }
         }
      }
   }

   return (line);
}

/**
 * Print statements will be different based on the datatype
 * #ifdef lets us conditionally compile code based on which type we are using 
 */

String* add_front(String *head, char* line, int bool){
   String * newString = malloc(sizeof(String));
   newString->value = malloc (sizeof(char) * strlen(line));
   strcpy (newString->value,line);
   newString->next = head;
/*   if (bool > 0){
      head->previous = newString;
   } */
   return newString;
}

void free_list (String *head){
   String * new_str = head;
   String * old_str = NULL;
   while (new_str != NULL) {
      old_str = new_str;
      new_str = new_str->next;
      free (old_str->value);
      free (old_str);
   }
}

void print_decoded_list (String *str, int correctShift, int length) {
   int i = 0;
   int j = 0;
   int len = length;
   String *copy = str;


   for (i = 0; i < length - 1; i++) {
      /* Cycles through linked list */
      while ((str != NULL) && (str->next!= NULL) && (j < len - 1)){
         str = str->next;
         j++;
      }

      printf ("%s\n", decode_text(str->value,correctShift));
      str = copy;
      len--;
      j = 0;
   }

   printf ("%s\n", decode_text(str->value,correctShift));

   /*
   while (str != NULL) {
      printf ("%s\n", decode_text (str->value, correctShift));
      str = str->previous;
   }
   */
}

void print_table (int *text_freq, int totalLetters, int totalChars) {
   /* Index variable */
   int i;

   printf ("Number of letters in the text = %d \t Number of characters in the text = %d\n", totalLetters, totalChars);
   printf ("Letter \t Frequency\n");

   /* Prints text frequencies*/
   for (i = 0; i < ALPHA_SIZE; i++){
      printf ("[%c] \t %d\n", i + ASCII_LETTER - CAPITAL_DIFFERENCE, text_freq[i]);
   }
}

void print_chi_values (int totalLetters, int *text_freq){
   int i;         /* Index variable */
   /* letter frequencies that are commonly found in the English language ([i] = 0 -> A, [i] = 25 -> Z)*/
   double EF [] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07707, 0.01929,
   0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.0236, 0.0015, 0.01974, 0.00074};  
   double chiSquaredNumerator;                           /* Calculates numerator of Chi Squared Formula */
   double tempChiResult = 0;                             /* Stores the Chi Result for each shift */
   
   int shiftNumber;                                      /* Tests each potential shift number as input for chi squared formula, increments from 0 to 25 */
   
   printf ("Shift Number \t Chi Squared Value\n");

   /* Tests each possible shift number used to encrypt text */
   for (shiftNumber = 0; shiftNumber < ALPHA_SIZE; shiftNumber++){
      /* Cycles through alphabet */
      for (i = 0; i < ALPHA_SIZE; i++) {
          /* Performs Chi-Squared formula calculation */
         chiSquaredNumerator = (totalLetters * EF[offset((char)(i + ASCII_LETTER))] - text_freq[offset(encode(i + ASCII_LETTER,shiftNumber))]);
         chiSquaredNumerator *= chiSquaredNumerator;
         tempChiResult += chiSquaredNumerator  / (totalLetters * totalLetters * EF[offset((char)(i + ASCII_LETTER))]);
      }

      printf ("[%d] \t\t %lf\n", shiftNumber, tempChiResult);

      /* Resets temporary variable */
      tempChiResult = 0;
   }

}