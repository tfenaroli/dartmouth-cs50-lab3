/*
Thomas Fenaroli
CS50
settest.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
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
    printf("starting testing!\n");
    int values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int index = 0;
    char* line;
    set_t* set1 = set_new();
    if (set1 == NULL) {
      fprintf(stderr, "bag_new failed for bag1\n");
      return 1;
    }

    // filling set1 with values
    printf("testing inserts\n");
    while (!feof(stdin)) {
        line = file_readLine(stdin);
        if (line != NULL) {
            if (set_insert(set1, line, &values[index])) {
                printf("inserted line: %s\n", line);
                printf("inserted int: %d\n\n", values[index]);
                index++;
            }
        }
        mem_free(line);
    }

    // testing set_print
    printf("testing set_print\n");
    set_print(set1, stdout, &intprint);

    printf("testing faulty inserts (NULL set, NULL item, NULL key)\n");
    // inserting NULL set, good item
    set_insert(NULL, "nullset", (int*)10);
    // inserting good set, NULL item
    set_insert(set1, "nullitem", NULL);
    // inserting good set, good item, NULL key
    set_insert(set1, NULL, (int*)10);
    // ensuring set1 isn't changed
    printf("The set shouldn't have changed because of faulty inserts\n");
    set_print(set1, stdout, &intprint);
    
    // testing set_find
    printf("testing set_find with valid key\n");
    char* testkey = "test4";
    int* testint = set_find(set1, testkey);
    printf("set_find test result using test key %s (should be 4) is: %d\n\n", testkey, *testint);

    printf("testing set_find with invalid key\n");
    testkey = "test11";
    void* testresult = set_find(set1, testkey);
    printf("set_find test result using test key %s (should be NULL) is: %s\n\n", testkey, (char*)testresult);

    // testing set_iterate
    printf("testing set_iterate");
    int setcount = 0;
    set_iterate(set1, &setcount, &itemcount);
    printf("setcount (should be 10) is: %d\n\n", setcount);

    printf("testing set_iterate with NULL inputs (nothing should happen)\n\n");
    set_iterate(set1, NULL, &itemcount);
    set_iterate(NULL, &setcount, &itemcount);
    set_iterate(set1, &setcount, NULL);

    // testing set_delete
    printf("testing set_delete\n");
    set_delete(set1, int_delete);
 
    // returns 0
    return 0;
}