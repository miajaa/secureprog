#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
using namespace std;

int main() {
    char userInput[256]; // Assuming a maximum length for the input

    /* userinput e.g. for Pointer address; Hi there i can see you: %p %p %p %p %p %p %p %p %p %p %p %p
    or Unsigned hexadecimal integer: Hi there %x %x %x %x %x %x %x %x %x %x

    When an attacker can control the format string passed to printf or
    similar functions, they may use format specifiers like %x to leak
    information from the stack or other areas of memory.

    The hexadecimal value 4c698a30 printed by the %x format specifier likely
    represents a memory address or some other data present in the stack or memory
    at the time of execution. The actual value will depend on the specific details
    of the program's memory layout and execution environment.*/

    printf("Enter command line argument: ");
    scanf("%[^\n]", userInput);

    // This line is safe
    printf("%s\n", userInput);


    // This line is vulnerable
    printf(userInput);

    return 0;
}
