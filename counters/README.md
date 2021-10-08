# CS50 Lab 3
## CS50 Fall 2021
## some copied from README.md in starter kit

### Counters

A counter set is a set of counters, each distinguished by an integer key. It's a set - each key can only occur once in the set - and it tracks a counter for each key. It starts empty. Each time counters_add is called on a given key, the corresponding counter is incremented. The current counter value can be retrieved by asking for the relevant key.

### Usage

```c
counters_t* counters_new(void);
int counters_add(counters_t* ctrs, const int key);
int counters_get(counters_t* ctrs, const int key);
bool counters_set(counters_t* ctrs, const int key, const int count);
void counters_print(counters_t* ctrs, FILE* fp);
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count));
void counters_delete(counters_t* ctrs);
```

### Implementation

We implement this counters as a linked list.

### Assumptions

No assumptions beyond those that are clear from the spec.

### Files

.gitignore
counters.c
counters.h
counterstest.c
Makefile
README.md
testing.out

### Compilation

To compile, simply make

### Testing

It tests a few error and edge cases.
This test is somewhat minimal.
A lot more could be done!

To test, simply make test &> testing.out.
See testing.out for details of testing and an example test run.

To test with valgrind, simply make valgrind.