// Copyright Lance Wallis, 2023, All Rights Reserved.

#include <iostream>
#include <cstdlib>
#include <string>

#include "logger/logger.h"
#include "utilities/platform.h"

using namespace std;

int main() {
    
    std::string exe_path = GetEXE();
    Log(LogLevel::info, "EXE Location: %s", exe_path.c_str());


    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    do {
        std::cout << '\n' << "Press the Enter key to continue.\n";
    } while (cin.get() != '\n');

    Logger* logger = logger->GetInstance();
    logger->shutdown();

    return 0;
}