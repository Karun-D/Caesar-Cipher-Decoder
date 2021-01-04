/**
 *  @file Q2.h
 *  @author Karunpreet Dhamnait
 *  @date Mar 2020
 *  @brief File Containing the function definitions for Assignment_3: Question #2
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

/**
 * String Data Type
 *    value: stores the content of a string in a dynamic character array
 *    String * next is used for INSERTION ORDER
 */

typedef struct String {
   char* value;   		
   struct String *next;  
} String;

/** 
 * Define statements for FAILURE and SUCCESS and program constants
 * We can use FAIL in place of 0
 * SUCCESS in place of 1
 * For greater human readability
 */
#define ASCII_LETTER 97
#define CAPITAL_DIFFERENCE 32
#define ALPHA_SIZE 26
#define MAX_SIZE 500
#define MAX_CHI_RESULT 161
#define SUCCESS 1
#define FAILURE 0

/**  
 * fileNameArgument 
 * Description: Searches for a file name in the command line using flag arguments
 * Returns:
 *    True - If name of text file is found 
 * 	  False - If no file name was entered in the command line
 * CHANGE TO find_file_name_argument
 */
char * fileNameArgument (int argc, char * argv[], char * flag);

/**  
 * flagArgument 
 * Description: Searches for a flag the command line
 * Returns:
 *    True - If flag is found 
 * 	  False - If no flag was entered in the command line
 * CHANGE TO find_flag_argument
 */
int flagArgument (int argc, char * argv[], char * flag);

/**  
 * letter_count 
 * Returns: Number of letters in a string (characters between A/a to Z/z) 
 */
int letter_count (char *str);

/**
 * create_freq_table
 * Returns: an empty 1d array (frequency table)
 *    each element of the array holds the numbers of times each letter (upper or lower case) occurs in the string that is passed in as an argument
 *    i.e. the first index holds the count for 'a' / 'A', the second index hold the count for 'b' / 'B', etc.
 */
int * create_freq_table ();

/**
 * create_freq_table
 * Description: updates frequency table by reading input one string at a time
 * CHANGE TO update_freq_table
 */
void add_letters(int *freq_table, char *string);

/**
 * offset
 * Returns: an integer representing the letter's index in an alphabet array
 * Description: Subfunction used in encode_shift for the Chi-Squared formula
 */
int offset (char letter);

/**
 * encode
 * Returns: a letter encrypted (using the shift number)
 * Description: Subfunction used in encode_shift for the Chi-Squared formula
 */
char encode (char letter, int shiftNumber);

/**
 * encode_shift
 * Returns: the shift number used to encode the input text using the Chi-Squared formula
 * Description: Calculated by finding the minimum chi-sq shift
 */
int encode_shift (int totalLetters, int *text_freq);

/**
 * decode_text
 * Returns: a decoded string 
 * Description: Solved by applying the shift value calculated in the "encode_shift" function
 */
char * decode_text (char * line, int shiftNumber);


/** 
 * add_front
 * Returns: a newly produced String
 * Description: Inserts the String using INSERTION order  
 */
String * add_front(String * head, char * line, int bool);

/** 
 * free_list
 * Description: destroys all Strings from the list
 *    frees the memory of each String and its values
 */ 
void free_list (String * head);

/** 
 * print_decoded_list
 * Description: Computes the character/letter count summary and frequency table and prints them to stdout using the list as input
 */ 
void print_decoded_list (String * str, int correctShift, int length);

/** 
 * print_table
 * Description: Computes the character/letter count summary and frequency table and prints them to stdout
 */ 
void print_table (int * text_freq, int totalLetters, int totalChars);

/** 
 * print_chi_values
 * Description: Computes the chi squared value for all shifts, printing them out along with their corresponding shift values
 */ 
void print_chi_values (int totalLetters, int * text_freq);

