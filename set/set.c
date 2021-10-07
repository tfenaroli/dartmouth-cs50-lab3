/* 
Thomas Fenaroli
CS50
set.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "../lib/mem.h"

// local type
typedef struct setnode {
  void* item;
  char* key;
  struct setnode *next;
} setnode_t;

// global type
typedef struct set {
  struct setnode *head;
} set_t;

// setnode_new creates setnode
static setnode_t* setnode_new(char* key, void* item) {
    setnode_t* node = mem_malloc(sizeof(setnode_t));
    printf("mallocd\n");

    if (node == NULL) {
        return NULL;
    }
    else {
        node->key = key;
        node->item = item;
        node->next = NULL;
        return node;
    }
}

// set_new (see set.h for description)
set_t* set_new(void) {
    set_t* set = mem_malloc(sizeof(set_t));
    printf("mallocd\n");
    if (set==NULL) {
        return NULL;
    }
    else {
        set->head = NULL;
        return set;
    }
}

// set_insert (see set.h for description)
bool set_insert(set_t* set, const char* key, void* item) {
    if (set == NULL || key == NULL || item == NULL) {
        return false;
    }
    setnode_t* current = set->head;
    
    while (current != NULL) {
        int comp = strcmp(key, current->key);
        if (comp == 0) {
            return false;
        }
        current = current->next;
    }
    // somethings funky around here

    // if set, key and item are not null
    // allocate memory for a char
    char* key_copy = mem_malloc(strlen(key) + 1);
    printf("malloc'd\n");
    // key_copy = key[0];
    strcpy(key_copy, key);


    setnode_t* new = setnode_new(key_copy, item);
    if (new != NULL) {
        new->next = set->head;
        set->head = new;
        return true;
    }
    return false;
}


// set_find (see set.h for description)
void* set_find(set_t* set, const char* key) {
    if (set == NULL || key == NULL) {
        return NULL;
    }
    setnode_t* current = set->head;
    while (current != NULL) {
        int comp = strcmp(key, current->key);
        if (comp == 0) {
            return current->item;
        }
        current = current->next;
    }
    return NULL;
}

// set_print (see set.h for description)
void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item)) {
    if (fp != NULL) {
        if (set != NULL) {
            setnode_t* current = set->head;
            fprintf(fp, "{");
            while (current != NULL) {
                if (itemprint != NULL) {
                    (*itemprint)(fp, current->key, current->item);
                    if (current->next != NULL) {
                        fprintf(fp, ",");
                        fprintf(fp, " \n");
                    }
                }
                current = current->next;
            }
            fprintf(fp, "}\n\n");
        }
        else {
            fprintf(fp, "(null)");
        }
    }
}

// set_iterate (see set.h for description)
void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) ) {
    if (set != NULL && itemfunc != NULL) {
        setnode_t* current = set->head;
        while (current != NULL) {
            (*itemfunc)(arg, current->key, current->item);
            current = current->next;
        }
    }
}

// set_delete (see set.h for description)
void set_delete(set_t* set, void (*itemdelete)(void* item) ) {
    if (set != NULL) {
        setnode_t* node = set->head;
        while (node != NULL) {
            if (itemdelete != NULL) {
                (*itemdelete)(node->item);
            }
            setnode_t* next = node->next;
            mem_free((char*)node->key);
            mem_free(node);
            node = next;
        }
        mem_free(set);
    }
}