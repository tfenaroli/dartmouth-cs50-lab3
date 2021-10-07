/*
Thomas Fenaroli
CS50
settest.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "../lib/file.h"

// intprint prints key and integer combo
void intprint(FILE* fp, char* key, void* item) {
  int* integerp = (int*) item;
  if (integerp == NULL) {
    fprintf(fp, "(null)");
  }
  else {
    fprintf(fp, "key integer pair is: (%s, %d)", key, *integerp); 
  }
}

// itemcount increments arg (function borrowed from bagtest.c code)
static void itemcount(void* arg, void* item) {
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
    while (!feof(stdin)) {
        line = file_readLine(stdin);
        if (line != NULL) {
            if (set_insert(set1, line, &values[index])) {
                printf("inserted line is this: %s\n", line);
                printf("inserted int is this: %d\n\n", values[index]);
                index++;
            }
        }
        mem_free(line);
    }

    // testing set_print
    set_print(set1, stdout, intprint);

    // inserting NULL set, good item
    set_insert(NULL, "nullset", 10);
    // inserting good set, NULL item
    set_insert(set1, "nullitem", NULL);
    // inserting good set, good item, NULL key
    set_insert(set1, NULL, 10);
    // ensuring set1 isn't changed
    printf("The set shouldn't have changed because of faulty inserts\n");
    set_print(set1, stdout, intprint);
    
    // testing set_find
    char* testkey = "test4";
    int* testint = set_find(set1, testkey);
    printf("set_find test result using test key %s (should be 4) is: %d\n\n", testkey, *testint);

    // testing set_iterate
    int setcount = 0;
    set_iterate(set1, &setcount, &itemcount);
    printf("setcount (should be 10) is: %d\n\n", setcount);

    // testing set_delete
    set_delete(set1, &int_delete);
 
    // returns 0
    return 0;
}