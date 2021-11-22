# Project 4 - Working with Threads and Condition Variables

## Source files:

The following source files are for use with Project 4. They present
lightweight C++ wrappers for POSIX threads, mutex locks, and condition
variables. Return values are checked, and any API calls that fail are
reported with appropriate error messages before exiting the program.

- `pthread-wrappers.cpp` (`Thread`, `Mutex`, and `Cond` wrappers)

- `pthread-wrappers.h` (header files containing class definitions)

## Example files:

This repository also includes versions of the example code from the
textbook that have been updated to use `pthread-wrappers.h` rather
than `common_threads.h`.

Note that unlike the examples posted to the course website, no
attempt has been made to render this sample code into idomatic C++.
Except for the switch to pthread-wrappers and changes necessary to
compile cleanly with C++, the code is remains as-is.

The only exception is `struct synchronizer_t` in `join_modular.cpp`,
which turns the sync "object" into an actual C++ object.

### Chapter 26 (`ostep-code/threads-intro`)
- `t0.cpp`
- `t1.cpp`

### Chapter 27 (`ostep-code/threads-api`)
- `thread_create.cpp`
- `thread_create_simple_args.cpp`
- `thread_create_with_return_args.cpp`

### Chapter 30 (`ostep-code/threads-cv`)

#### Fork/Join Problem
- `join_spin.cpp`
- `join_no_lock.cpp`
- `join_no_state_var.cpp`
- `join.cpp`
- `join_modular.cpp`

#### Producer/Consumer Problem
- `pc.cpp`
- `pc_single_cv.cpp`
