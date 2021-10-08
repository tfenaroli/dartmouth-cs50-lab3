# CS50 Lab 3
## CS50 Fall 2021
## some copied from README.md in starter kit

### Set

A set maintains an unordered collection of (key,item) pairs; any given key can only occur in the set once. It starts out empty and grows as the caller inserts new (key,item) pairs. The caller can retrieve items by asking for their key, but cannot remove or update pairs. Items are distinguished by their key.

### Usage

```c
set_t* set_new(void);
bool set_insert(set_t* set, const char* key, void* item);
void* set_find(set_t* set, const char* key);
void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item) );
void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void set_delete(set_t* set, void (*itemdelete)(void* item) );
```

### Implementation

We implement this set as a linked list.

### Assumptions

No assumptions beyond those that are clear from the spec.

### Files

.gitignore
Makefile
README.md
set.c
set.h
settest.c
testing.out
testkeys.txt

### Compilation

To compile, simply make

### Testing

It tests a few error and edge cases.
This test is somewhat minimal.
A lot more could be done!

To test, simply make test &> testing.out.
See testing.out for details of testing and an example test run.

To test with valgrind, simply make valgrind.