/**
 *  @file Q1.h
 *  @author Karunpreet Dhamnait
 *  @date Mar 2020
 *  @brief File Containing the function definitions for Assignment_3: Question #1
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
   char* value;   /* String content */
   struct String *next;  /* String pointer */
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

/**  
 * letter_count 
 * Returns: Number of letters in a string (characters between A/a to Z/z) 
 */
int letter_count ( char * str );

/**
 * frequency_table
 * Returns: a 1d array
 *    each element of the array holds the numbers of times each letter (upper or lower case) occurs in the string that is passed in as an argument
 *    i.e. the first index holds the count for 'a' / 'A', the second index hold the count for 'b' / 'B', etc.
 */
int * frequency_table ( char * str );
