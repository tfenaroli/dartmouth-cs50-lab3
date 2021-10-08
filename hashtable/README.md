# CS50 Lab 3
## CS50 Fall 2021
## some copied from README.md in starter kit

### Hashtable

A hashtable is a set of (key,item) pairs. It acts just like a set, but is far more efficient for large collections.

### Usage

```c
hashtable_t* hashtable_new(const int num_slots);
bool hashtable_insert(hashtable_t* ht, const char* key, void* item);
void* hashtable_find(hashtable_t* ht, const char* key);
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item));
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) );
```

### Implementation

We implement this hashtable as an array of sets.

### Assumptions

No assumptions beyond those that are clear from the spec.

### Files

.gitignore
hash.c
hash.h
hashtable.c
hashtable.h
hashtabletest.c
Makefile
README.me

### Compilation

To compile, simply make

### Testing

It tests a few error and edge cases.
This test is somewhat minimal.
A lot more could be done!

To test, simply make test &> testing.out.
See testing.out for details of testing and an example test run.

To test with valgrind, simply make valgrind.