A basic process scheduler example for Linux
===========================================
Written by Felix Stegmaier

0. tl;dr
--------
This is a simple process scheduler for Linux
that executes multiple processes pseudo-simultaneously
using a round robin algorithm.

Build with project by executing `make` in the main folder.  
Start the example program by executing `main`.  

1. Requirement
--------------
This project is part of my Operating Systems I lecture.  
The literal exercise was to write a "basic process scheduler."  
What was meant by this is that I should write a program
that demonstrates how to create processes and schedule them,
so that only one process is active at a time and the processes
still appear as to be pseudo-parallel, i.e. they run in alternation.


2. Specification
----------------



3. Testing
----------
The program should include several test cases.
These test cases create multiple "tasks" as processes to be
scheduled by the scheduler and perform different actions on them
(e.g. joining, pausing and killing in various orders).
Each of these tasks runs in pseudo-parallel and counts up a variable
which it outputs to the console.

1. Create 3 processes and join with them.
2. Create 3 processes, pause one of them, join with the other two, continue the former and join it.
3. Create 3 processes, pause one, kill another one, continue the former and wait for all living processes to finish.
4. Create 3 processes, kill all of them.

The test cases are chosen, so that all functionalities in various orders are covered.



4. Running
----------
Build with project by executing `make` in the main folder.  
Start the example program by executing `build/main`.  

All the tests specified in 3. will be executed now
and you will see the output of the tests.

Clean the projects `build` folder by running `make clean`.


5. How it is implemented
------------------------


6. Conclusion
-------------
