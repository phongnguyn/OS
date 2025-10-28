README.template

## Project Number/Title

* Authors: Tan Loc Nguyen, Shijie Tian, Lehao Huang
* Group name: Assignment_3_Groups 148

## Overview

This program implements a parallel version of the merge sort algorithm using pthreads. 
It demonstrates how multithreading can significantly improve sorting performance on multi-core 
systems by dividing the sorting work across multiple threads.

## Manifest

- `mergesort.c` - Main implementation of parallel merge sort algorithm
- `mergesort.h` - Header file with function prototypes and data structures 
- `test-mergesort.c` - Testing program with timing and validation functions
- `Makefile` - Build configuration for compilation
- `README.md` - Project documentation (this file)

## Building the project

all needed to do is compile the code by running

```
make test-mergesort
```

## Features and usage

The program features:
    - Multi-threaded merge sort using pthreads
    - Configurable thread levels via cutoff parameter
    - Memory-safe implementation with proper allocation/deallocation
    - Performance timing and validation
Usage:

```
./test-mergesort <input_size> <cutoff_level> <seed>
```

Example:

```
./test-mergesort 100000000 0 1234
```

```
./test-mergesort 100000000 2 1234
```

```
./test-mergesort 100000000 3 1234
```

## Testing

We conducted comprehensive testing:

1. Functionality Testing
   - Tested arrays from size 10 to 100,000,000 elements
   - Verified all cutoff levels (0-4) produce correct sorted results
   - Used multiple random seeds to ensure consistency
2. Memory Testing
   - Used Valgrind to detect memory leaks: "All heap blocks were freed -- no leaks are possible"
   - Verified no double-free errors or memory corruption
3. Performance Testing
   - Serial version (cutoff=0): 14.80 seconds for 100,000,000 elements
   - Parallel version (cutoff=2): 4.77 seconds (3.10x speedup)
   - Parallel version (cutoff=3): 3.17 seconds (4.67x speedup)
   - Parallel version (cutoff=4): 2.33 seconds (6.35x speedup)
     All tests exceeded the requirement of 2x speedup.

## Known Bugs

No known bugs. The implementation passes all functionality, memory, and performance tests.

## Reflection and Self Assessment



It has been a while since merge sort was mentioned so I quickly look the merge mechanism and divide and conquer approach of this sorting method.  

Small warnings appeared is calling free(args) inside `parallel_mergesort` while the pointer is already deallocated by the parent thread or by the function that call `parallel_mergesort`. 

the challenging of the project was to optimize the runtime of the code by recognizing that running mergesort serially for the size of the sub-array 1000 is faster than running it in parallel. 

## Sources Used

my_mergesort and merge function are referenced from https://www.geeksforgeeks.org/dsa/merge-sort/
pthread_create and pthread_join template is from https://www.geeksforgeeks.org/c/thread-functions-in-c-c/

memcpy parameter references: https://cplusplus.com/reference/cstring/memcpy/
