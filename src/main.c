/**
 * File: main.c
 * Author: Felix Stegmaier
 * Created on: 04.11.2016
 */

#include <stdio.h>
#include "../h/tests.h"

int main(int argc, char const *argv[]) {
  void (*tests[TESTS_NUMBER])(void) = {test1, test2, test3, test4};
  for (size_t i = 0; i < TESTS_NUMBER; i++) {
    printf("===============================\nExecuting test %lu\n===============================\n", i+1);
    tests[i]();
  }
  return 0;
}
