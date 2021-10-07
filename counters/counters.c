/* 
Thomas Fenaroli
CS50
counters.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "../lib/mem.h"

// local type
typedef struct countersnode {
  int count;
  int key;
  struct countersnode *next;
} countersnode_t;

// global type
typedef struct counters {
  struct countersnode *head;
} counters_t;

// countersnode_new creates countersnode
static countersnode_t* countersnode_new(int key) {
    countersnode_t* node = mem_malloc(sizeof(countersnode_t));

    if (node == NULL) {
        return NULL;
    }
    else {
        node->key = key;
        node->count = NULL;
        node->next = NULL;
        return node;
    }
}

// counters_new (see counters.h for description)
counters_t* counters_new(void) {
    counters_t* counters = mem_malloc(sizeof(counters_t));
    if (counters == NULL) {
        return NULL;
    }
    else {
        counters->head = NULL;
        return counters;
    }
}

// counters_insert (see counters.h for description)
int counters_add(counters_t* ctrs, const int key) {
    if (ctrs == NULL || key < 0) {
        return 0;
    }

    countersnode_t* current = ctrs->head;
    while (current != NULL) {
        if (key == current->key) {
            current->count++;
            return current->count;
        }
        current = current->next;
    }

    // if counters, key and item are not null
    // allocate memory for a char

    countersnode_t* new = countersnode_new(key);

    if (new != NULL) {
        new->count = 1;
        new->next = ctrs->head;
        ctrs->head = new;
        return 1;
    }
    return 0;
}

// counters_find (see counters.h for description)
int counters_get(counters_t* ctrs, const int key) {
    if (ctrs == NULL) {
        return 0;
    }
    countersnode_t* current = ctrs->head;
    while (current != NULL) {
        if (current->key == key) {
            return (current->count);
        }
        current = current->next;
    }
    return 0;
}

bool counters_set(counters_t* ctrs, const int key, const int count) {
    if (ctrs == NULL || key < 0 || count < 0) {
        return false;
    }
    countersnode_t* current = ctrs->head;
    while (current != NULL) {
        if (current->key == key) {
            current->count = count;
            return true;
        }
        current = current->next;
    }
    countersnode_t* new = countersnode_new(key);
    if (new != NULL) {
        new->count = count;
        new->next = ctrs->head;
        ctrs->head = new;
        return true;
    }
    return false;
}

// counters_print (see counters.h for description)
void counters_print(counters_t* ctrs, FILE* fp) {
    if (fp != NULL) {
        if (ctrs != NULL) {
            countersnode_t* current = ctrs->head;
            fprintf(fp, "{");
            while (current != NULL) {
                fprintf(fp, "(%d, %d)", current->key, current->count);
                if (current->next != NULL) {
                    fprintf(fp, ", \n");
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

//counters_iterate (see counters.h for description)
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count) ) {
    if (ctrs != NULL && itemfunc != NULL) {
        countersnode_t* current = ctrs->head;
        while (current != NULL) {
            (*itemfunc)(arg, current->key, current->count);
            current = current->next;
        }
    }
}

// counters_delete (see counters.h for description)
void counters_delete(counters_t* ctrs) {
    if (ctrs != NULL) {
        countersnode_t* node = ctrs->head;
        while (node != NULL) {
            countersnode_t* next = node->next;
            mem_free(node);
            node = next;
        }
        mem_free(ctrs);
    }
}