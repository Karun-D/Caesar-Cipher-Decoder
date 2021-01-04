/*ALL documentation in associated .h file*/

#include "Q3.h"

Record* add_record (Record *head, tempRecord * temp) {
   int i;

   Record * newRecord = malloc (sizeof(Record));
   strcpy (newRecord->stringOne, temp->stringOne);
   strcpy (newRecord->stringTwo, temp->stringTwo);

   for (i = 0; i < 24; i++) {
       newRecord->doubleArr[i] = temp->doubleArr[i]; 
/*       printf ("doubleArr[%d] = %lf\n", i,temp->doubleArr[i]); 
       printf ("newRecordDoubleArr[%d] = %lf\n", i, newRecord->doubleArr[i]); */
      if (i < 12){ 
        newRecord->intArr[i] = temp->intArr[i]; 
/*        printf ("intArr[%d] = %d\n", i, temp->intArr[i]); 
        printf ("newRecordintArr[%d] = %d\n", i, newRecord->intArr[i]);  */
      }
   }
   

   newRecord->next = head; 

   return newRecord;
}

void print_record (Record* rec) {
   int i;

   printf ("%s\n",rec->stringOne);
   for (i = 0; i < 24; i++) {
      if (i < 23) {
         printf ("%0.2lf, ", rec->doubleArr[i]);
   continue ;
      }
      printf ("%0.2lf\n", rec->doubleArr[i]);
   } 

   printf ("%s\n",rec->stringTwo);
   for (i = 0; i < 12; i++) {
      if (i < 11) {
         printf ("%d, ", rec->intArr[i]);
   continue ;
      }
      printf ("%d\n", rec->intArr[i]);
   } 

   printf ("\n");

}

void print_all_records (Record *head, int numOfRecords) {
   int i =0;
   int j = 0;
   int length = numOfRecords;
   Record *headCopy = head;

   for (i = 0; i < numOfRecords - 1; i++) {
      while ((head != NULL) && (head->next!=NULL) && (j < length -1)) {
         head = head->next;
         j++;
      }

      print_record (head); 
      head = headCopy;
      length--;
      j = 0;

   }

   print_record(head);
}

void print_reverse (Record *head) {
   while (head!=NULL) {
      print_record(head);
      head = head->next;
   }
}

void write_record (Record* rec, FILE * fileName) {
   int i;
   tempRecord *temp = malloc (sizeof(tempRecord));

   strcpy (temp->stringOne, rec->stringOne);
   strcpy (temp->stringTwo, rec->stringTwo);

   for (i = 0; i < 24; i++) {
       temp->doubleArr[i] = rec->doubleArr[i]; 
/*       printf ("doubleArr[%d] = %lf\n", i,temp->doubleArr[i]); 
       printf ("newRecordDoubleArr[%d] = %lf\n", i, newRecord->doubleArr[i]); */
      if (i < 12){ 
        temp->intArr[i] = rec->intArr[i]; 
/*        printf ("intArr[%d] = %d\n", i, temp->intArr[i]); 
        printf ("newRecordintArr[%d] = %d\n", i, newRecord->intArr[i]);  */
      }
   }

   fwrite(temp, sizeof(tempRecord), 1,fileName);
   free (temp);
}

void write_all_records (Record *head, int numOfRecords, FILE * fileName) {
   int i =0;
   int j = 0;
   int length = numOfRecords;
   Record *headCopy = head;

   for (i = 0; i < numOfRecords - 1; i++) {
      while ((head != NULL) && (head->next!=NULL) && (j < length -1)) {
         head = head->next;
         j++;
      }

      write_record (head, fileName); 
      head = headCopy;
      length--;
      j = 0;
   }

   write_record (head, fileName); 
}

void write_reverse (Record *head, FILE *fileName) {
   while (head != NULL) {
      write_record(head, fileName);
      head = head->next;
   }
}

void free_records (Record *head){
   Record * newRecord = head;
   Record * oldRecord = NULL;
   while (newRecord != NULL) {
      oldRecord = newRecord;
      newRecord = newRecord->next;
      free (oldRecord);
   }
}
