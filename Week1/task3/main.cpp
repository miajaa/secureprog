#include <iostream>

using namespace std;

int main()
{
    // Size of the character buffers
    const int BufferSize = 32;
    // Overflow size to simulate heap overflow
    const int OverflowSize = 12;
    // Difference in memory addresses between the two buffers
    unsigned int bufferDifference;

    char *firstBuffer = new char[BufferSize];   // Allocate memory for the first buffer
    char *secondBuffer = new char[BufferSize];  // Allocate memory for the second buffer

    // Calculate the difference between the starting addresses of the two buffers
    bufferDifference = static_cast<unsigned int>(secondBuffer - firstBuffer);

    // Print memory addresses and the calculated difference
    std::cout << "firstBuffer = " << static_cast<void*>(firstBuffer) << endl
              << "secondBuffer = " << static_cast<void*>(secondBuffer)
              << endl << "bufferDifference = 0x" << hex << bufferDifference << " bytes" <<endl;

    // Fill the secondBuffer with 'X' characters, leaving room for the null terminator
    for (int i = 0; i < BufferSize - 1; ++i)
        secondBuffer[i] = 'X';
    secondBuffer[BufferSize - 1] = '\0';

    // Print the content of secondBuffer before the simulated overflow
    std::cout << "before overflow: secondBuffer = " << secondBuffer <<endl;

    // Simulate a heap overflow by writing 'Y' beyond the allocated space of firstBuffer
    for (unsigned int i = 0; i < bufferDifference + OverflowSize; ++i)
        firstBuffer[i] = 'Y';

    // Print the content of secondBuffer after the simulated overflow
    std::cout << "after overflow: secondBuffer = " << secondBuffer << endl;

    // Clean up: release allocated memory
    delete[] firstBuffer;
    delete[] secondBuffer;

    // In conclusion: The heap overflow occurred because we wrote 'Y' beyond the allocated space of firstBuffer.
    // This affected the memory layout, causing the secondBuffer to reflect the changes made to the firstBuffer.
    // As a result, the printout of secondBuffer after the overflow is different from the original content.

    return 0;
}
