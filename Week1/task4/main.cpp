#include <iostream>
#include <cstring>

using namespace std;

void FunctionA() {
    cout << "Function A" << endl;
}


void FunctionC() {
    cout << "Function C" << endl;
}

int main() {
    void (*funcptr)();

    // Initialize funcptr to FunctionA
    funcptr = FunctionA;

    cout << "Before overflow - funcptr points to FunctionA at address: " << hex << (size_t)funcptr << endl;
    cout << "FunctionA is at address: " << hex << (size_t)FunctionA << endl;
    cout << "FunctionC is at address: " << hex << (size_t)FunctionC << endl;

    // Hardcoded input to simulate a pointer overflow
    const char* userInput = "MaliciousInput123456789";

    // Assuming sizeof(void (*)()) is the size of a function pointer
    // This is platform-specific and may need adjustment
    memcpy(&funcptr, userInput, sizeof(void (*)()));

    cout << "After overflow - funcptr points to: " << hex << (size_t)funcptr << endl;

    // Now, let's modify the funcptr to point to FunctionC
    funcptr = FunctionC;

    cout << "After modifying funcptr - funcptr points to: " << hex << (size_t)funcptr << endl;

    return 0;
}
