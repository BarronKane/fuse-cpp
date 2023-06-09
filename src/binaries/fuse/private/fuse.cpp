// Copyright Lance Wallis, 2023, All Rights Reserved.

#include <iostream>
#include <cstdlib>
#include <string>

#include "logger/logger.h"
#include "utilities/platform.h"

int guarded_main()
{

    return 0;
}

int main() 
{
    
    std::string exe_path = GetEXE().string();
    Log(LogLevel::info, "EXE Location: {}", exe_path);

    int result = guarded_main();

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    
    do {
        std::cout << '\n' << "Press the Enter key to continue.\n";
    } while (std::cin.get() != '\n');

    Logger* logger = logger->GetInstance();
    logger->shutdown();

    return result;
}
