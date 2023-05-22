// Copyright Lance Wallis, 2023, All Rights Reserved.

#include <iostream>
#include <cstdlib>
#include <string>

#include "logger/logger.h"

using namespace std;

int main() {
    // Logger test.
    Log(LogLevel::info, "Test Log.");
    
    system("pause");
    return 0;
}