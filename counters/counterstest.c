/*
Thomas Fenaroli
CS50
counterstest.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
//#include "../lib/file.h"

// itemcount increments arg (function borrowed from bagtest.c code)
static void itemcount(void* arg, const int key, const int count) {
  int* nitems = arg;

  if (nitems != NULL && key > 0 && count >0) {
    (*nitems)++;
  }
}

// main function
int main(){
    printf("starting testing!\n\n");
    int values[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    counters_t* counters1 = counters_new();
    printf("made new counter\n");
    if (counters1 == NULL) {
      fprintf(stderr, "bag_new failed for bag1\n");
      return 1;
    }

    // testing counters_add with unique keys
    printf("testing counters_add with unique keys\n");
    for (int index = 0; index < 10; index++) {
      printf("added with key: %d\n\n", values[index]);
      counters_add(counters1, values[index]);
    }

    printf("testing counters_print\n");
    // testing counters_print
    counters_print(counters1, stdout);

    // testing counters_add with existing keys
    printf("testing counters_add with existing keys\n");
    for (int i = 0; i < 50; i++) {
      counters_add(counters1, 4);
    }
    for (int i = 0; i < 10; i++) {
      counters_add(counters1, 6);
    }
    for (int i = 0; i < 15; i++) {
      counters_add(counters1, 9);
    }

    // confirming add worked
    printf("Should have different values for keys 4 (51), 6 (11), and 9 (16)\n");
    counters_print(counters1, stdout);

    // testing counters_add with NULL set
    printf("testing counters_add with NULL set (shouldn't change set1)\n");
    counters_add(NULL, 8);

    // confirming add to NULL set didn't work
    printf("Set should not have different values from adding to a NULL set\n");
    counters_print(counters1, stdout);

    // testing counters_get
    printf("testing counters_get with key 6 (should return 11)\n");
    int result = counters_get(counters1, 6);
    printf("Result is: %d\n\n", result);

    printf("testing counters_get with invalid key 11 (should return 0)\n");
    result = counters_get(counters1, 11);
    printf("Result is: %d\n\n", result);

    // testing counters_set
    printf("testing counters_set (setting key 3 to count 348, key 2 to count 45, and key 6 to count 1)\n");
    counters_set(counters1, 3, 348);
    counters_set(counters1, 2, 45);
    counters_set(counters1, 6, 1);
    counters_print(counters1, stdout);

    // testing counters_iterate
    printf("testing counters_iterate by counting how many counters there are\n");
    int counterscount = 0;
    counters_iterate(counters1, &counterscount, &itemcount);
    printf("counterscount (should be 10) is: %d\n\n", counterscount);

    // testing counters_delete
    printf("testing counters_delete\n");
    counters_delete(counters1);
 
    // returns 0
    return 0;
}