#include <iostream>
#include <cstring>

using namespace std;

void offByOneBufferOverflow(const char *str, int size) {
    int i;
    char buffer[145];

     // Counter for characters copied into the buffer
    int charactersCopied = 0;

    // <= here is executed 145 + 1 times, leading to off by one buffer overflow
    for (i = 0; i <= 145 && i < size; i++) {
        buffer[i] = str[i];
        charactersCopied++;
    }

    cout << "Buffer contents: " << buffer << endl;
    cout << "Characters copied into the buffer: " << charactersCopied << endl;
}

int main() {
    const char *text =
        "He told them tales of bees and flowers, the ways of trees, and the strange creatures of the Forest, "
        "about the evil things and the good things, things friendly and things unfriendly, cruel things and kind things, "
        "and secrets hidden under brambles.";

    // Call the function with the provided text
    offByOneBufferOverflow(text, strlen(text));

    return 0;
}
