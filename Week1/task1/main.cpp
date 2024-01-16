#include <iostream>
#include <cstdio>

using namespace std;

// Function that demonstrates buffer overflow
void bufferOverflow(int loopSize) {
    int i;
    char customBuffer[123];

    // Looping beyond the size of customBuffer can lead to buffer overflow
    // In this example, 'C' is written to customBuffer, potentially overwriting
    // memory beyond its allocated space, causing undefined behavior.
    for (i = 0; i < loopSize; i++)
        customBuffer[i] = 'C';
}

int main() {
    int index, loopSize;

    cout << "Enter a number for the loop: ";
    cin >> loopSize;

    char customBuffer[123];

    // Initialize customBuffer with 'H' characters using a loop
    for (index = 0; index < loopSize; index++)
        customBuffer[index] = 'H';

    // Call the custom function to demonstrate buffer overflow
    bufferOverflow(loopSize);

    cout << "Completed without buffer overflow"<<endl ;
    return 0;
}
