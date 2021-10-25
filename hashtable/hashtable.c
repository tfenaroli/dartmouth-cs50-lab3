 /* 
Thomas Fenaroli
CS50
hashtable.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "../set/set.h"
#include "../lib/mem.h"
#include "hash.h"

// hashtable struct
typedef struct hashtable {
  int num_slots;
  set_t** set_array;
} hashtable_t;

// keyprint prints key if itemprint pointer parameter is NULL for hashtable_print function
void keyprint(FILE* fp, const char* key, void* item) {
  fprintf(fp, "key %s", key);
}

// hashtable_new (see hashtable.h for description)
hashtable_t* hashtable_new(const int num_slots) {
  if (num_slots <= 0) {
    return NULL;
  }
  hashtable_t* hashtable = mem_malloc(sizeof(hashtable_t));
  hashtable->set_array = mem_calloc(num_slots, sizeof(hashtable->set_array));
  hashtable->num_slots = num_slots;
  for (int i = 0; i < num_slots; i++) {
    (hashtable->set_array[i]) = set_new();
  }
  return hashtable;
}

// hashtable_insert (see hashtable.h for description)
bool hashtable_insert(hashtable_t* ht, const char* key, void* item) {
  if (ht == NULL || key == NULL || item == NULL) {
    return false;
  }
  for (int i = 0; i < ht->num_slots; i++) {
    if (set_find((ht->set_array)[i], key) != NULL) {
    return false;
    }
  }
  char* key_copy = mem_malloc(strlen(key) + 1);
  strcpy(key_copy, key);

  int index = hash_jenkins(key_copy, ht->num_slots);
  set_insert((ht->set_array[index]), key_copy, item);
  free(key_copy);
  return true;
}

// hashtable_find (see hashtable.h for description)
void* hashtable_find(hashtable_t* ht, const char* key) {
  if (ht == NULL || key == NULL){
    return NULL;
  }
  int index = hash_jenkins(key, ht->num_slots);
  return set_find(ht->set_array[index], key);
}

// hashtable_print (see hashtable.h for description) (prints each slot as a set
// of brackets instead of a new line, approved by Professor Palmer)
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item)) {
  if (fp != NULL && ht != NULL) {
    if (itemprint == NULL) {
      for (int i = 0; i < ht->num_slots; i++) {
        set_print((ht->set_array[i]), fp, keyprint);
      }
      fprintf(fp, "\n");
    }
    else {
      for (int i = 0; i < ht->num_slots; i++) {
        set_print((ht->set_array[i]), fp, itemprint);
        fprintf(fp, "\n");
      }
    }
  }
  else {
    fprintf(fp, "null");
  }
}

// hashtable_iterate (see hashtable.h for description)
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) ) {
  if (ht != NULL && itemfunc != NULL) {
    for (int i = 0; i < ht->num_slots; i++) {
      set_iterate(ht->set_array[i], arg, itemfunc);
    }
  }
}

// hashtable_delete (see hashtable.h for description)
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) ) {
  if (ht != NULL && itemdelete != NULL) {
    for (int i = 0; i < ht->num_slots; i++) {
      set_delete(ht->set_array[i], itemdelete);
    }
  }
  mem_free(ht->set_array);
  mem_free(ht);
}