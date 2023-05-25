// Copyright Lance Wallis, 2023, All Rights Reserved.

#include <iostream>
#include <cstdlib>
#include <string>

#include "logger/logger.h"
#include "utilities/platform.h"

using namespace std;

int main() {
    std::cout << "C++ Standard: " << __cplusplus << std::endl;

    // Logger test.
    Log(LogLevel::info, "Test Log. Number: %d", 1);
    Log(LogLevel::info, "Test Log. Number: %d", 2);
    Log(LogLevel::info, "Test Log. Number: %d", 3);
    Log(LogLevel::info, "Test Log. Number: %d", 4);
    
    do {
        std::cout << '\n' << "Press the Enter key to continue.";
    } while (cin.get() != '\n');

    Logger* logger = logger->GetInstance();
    logger->shutdown();

    return 0;
}