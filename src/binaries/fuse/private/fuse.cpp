// Copyright Lance Wallis, 2023, All Rights Reserved.

#include <iostream>
#include <cstdlib>
#include <string>

#include "logger/logger.h"
#include "utilities/platform.h"

using namespace std;

int main() {
    // Logger test.
    uint16 i = 32;
    Log(LogLevel::info, "Test Log. Number: %d", i);
    
    do {
        std::cout << '\n' << "Press the Enter key to continue.";
    } while (cin.get() != '\n');

    return 0;
}