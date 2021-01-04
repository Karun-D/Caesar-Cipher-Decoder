/**
 *  @file Q3.h
 *  @author Karunpreet Dhamnait
 *  @date Mar 2020
 *  @brief File Containing the function definitions for Assignment_3: Question #3
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

/**
 * Record Data Type
 *    Used to store a list of records
 */

typedef struct Record{
   char stringOne[24];   
   double doubleArr[24];
   char stringTwo[144];
   int intArr[12]; 
   struct Record *next;
}Record;

/**
 * Temporary Record Data Type
 *    Used to store a list of record temporarily before appending to Record list
 */
typedef struct tempRecord{
   char stringOne[24];   /* String content */
   double doubleArr[24];
   char stringTwo[144];
   int intArr[12]; 
}tempRecord;

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
 * add_record
 * Returns: a newly produced Record
 * Description: Inserts the Record using INSERTION order 
 */
Record * add_record (Record * head, tempRecord * temp);

/**
 * print_record
 * Description: Prints the contents of a record, used as a support function for print_all_records
 */
void print_record (Record* rec);

/**
 * print_all_records
 * Description: Prints the contents of each record in a linked list
 */
void print_all_records (Record * head, int numOfRecords);

/**
 * print_reverse
 * Description: Prints the contents of each record in a linked list in reverse order
 */
void print_reverse (Record * head);

/**
 * write_record
 * Description: Writes a record to a text file, used as a support function for write_all_records
 */
void write_record (Record * rec, FILE * fileName);

/**
 * write_all_records
 * Description: Writes all records in a linked list to a text file
 */
void write_all_records (Record * head, int numOfRecords, FILE * fileName);

/**
 * write_reverse
 * Description: Writes all records in a linked list to a text file in reverse order
 */
void write_reverse (Record * head, FILE * fileName);

/**
 * free_records
 * Description: destroys all Records from the linked list
 *    frees the memory of each Records and its contents
 */
void free_records (Record * head);

