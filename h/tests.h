/**
 * File: tests.h
 * Author: Felix Stegmaier
 * Created on: 04.11.2016
 *
 * Testcases for the scheduler that will be
 * executed by the main prorgam.
 * Before the tests are executed, the main program will initialize the scheduler.
 *
 */

#include "scheduler.h"

#ifndef TESTS_H
#define TESTS_H

/* time delay for counting up in microseconds */
#define COUNT_DELAY 2000UL  /* 2 milliseconds*/

/* how many tests are there */
#define TESTS_NUMBER 4

/**
 * Functions that are run in parallel.
 * They just output their name and count up to 10 with a delay of
 */
 void task1(void);
 void task2(void);
 void task3(void);

 /**
  * [test1 description]
  */
 void test1(void);

 /**
  * [test2 description]
  */
 void test2(void);

 /**
  * [test3 description]
  */
 void test3(void);

 /**
  * [test4 description]
  */
 void test4(void);

#endif /* TESTS_H */
