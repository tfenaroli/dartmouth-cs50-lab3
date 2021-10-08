/*
Thomas Fenaroli
CS50
hashtabletest.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "../lib/mem.h"
#include "../lib/file.h"

// intprint prints key and integer combo
void intprint(FILE* fp, const char* key, void* item) {
  int* integerp = (int*) item;
  if (integerp == NULL) {
    fprintf(fp, "(null)");
  }
  else {
    fprintf(fp, "(%s, %d)", key, *integerp); 
  }
}

// itemcount increments arg (function borrowed from bagtest.c code)
static void itemcount(void* arg, const char* key, void* item) {
  int* nitems = arg;

  if (nitems != NULL && item != NULL)
    (*nitems)++;
}

// int_delete deletes item (no item to free)
void int_delete(void* item) {
  if (item != NULL) {
    //mem_free(item);
  }
}

// main function
int main(){
    printf("starting testing!\n\n");
    int values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int index = 0;
    int slots = 5;
    char* line;
    hashtable_t* hashtable1 = hashtable_new(slots);
    if (hashtable1 == NULL) {
      fprintf(stderr, "bag_new failed for bag1\n");
      return 1;
    }
    printf("made table successfully\n\n");

    // filling hashtable1 with values
    printf("testing inserts\n");
    while (!feof(stdin)) {
        line = file_readLine(stdin);
        if (line != NULL) {
            if (hashtable_insert(hashtable1, line, &values[index])) {
                printf("inserted line: %s\n", line);
                printf("inserted int: %d\n\n", values[index]);
                index++;
            }
        }
        mem_free(line);
    }

    // testing hashtable_print (prints each slot as a set 
    // of brackets instead of a new line, approved by Professor Palmer)
    printf("testing hashtable_print\n");
    hashtable_print(hashtable1, stdout, &intprint);

    // testing hashtable_print with NULL function pointer (prints each slot as a set 
    // of brackets instead of a new line, approved by Professor Palmer)
    printf("testing hashtable_print\n");
    hashtable_print(hashtable1, stdout, NULL);

    printf("testing faulty inserts (NULL hashtable, NULL item, NULL key)\n");
    // inserting NULL hashtable, good item
    hashtable_insert(NULL, "nullhashtable", (int*)10);
    // inserting good hashtable, NULL item
    hashtable_insert(hashtable1, "nullitem", NULL);
    // inserting good hashtable, good item, NULL key
    hashtable_insert(hashtable1, NULL, (int*)10);
    // ensuring hashtable1 isn't changed
    printf("The hashtable shouldn't have changed because of faulty inserts\n\n");
    hashtable_print(hashtable1, stdout, &intprint);
    
    // testing hashtable_find
    printf("testing hashtable_find with valid key\n");
    char* testkey = "test8";
    int* testint = hashtable_find(hashtable1, testkey);
    printf("hashtable_find test result using test key %s (should be 8) is: %d\n\n", testkey, *testint);

    printf("testing hashtable_find with invalid key\n");
    testkey = "test11";
    void* testresult = hashtable_find(hashtable1, testkey);
    printf("hashtable_find test result using test key %s (should be NULL) is: %s\n\n", testkey, (char*)testresult);

    // testing hashtable_iterate
    printf("testing hashtable_iterate\n");
    int hashtablecount = 0;
    hashtable_iterate(hashtable1, &hashtablecount, &itemcount);
    printf("hashtablecount (should be 10) is: %d\n\n", hashtablecount);

    // testing hashtable_iterate with NULL inputs
    printf("testing hashtable_iterate with NULL inputs (nothing should happen)\n\n");
    hashtable_iterate(hashtable1, NULL, &itemcount);
    hashtable_iterate(NULL, &hashtablecount, &itemcount);
    hashtable_iterate(hashtable1, &hashtablecount, NULL);

    // testing hashtable_delete
    printf("testing hashtable_delete\n");
    hashtable_delete(hashtable1, int_delete);
 
    // returns 0
    return 0;
}