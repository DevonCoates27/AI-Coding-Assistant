#include "customjob.h"
#include <iostream>
#include <string>
#include <array>
#include <fstream>

void CustomJob::Execute(){
    std::string command = "python3 ./Code/sendPrompt.py";
    system(command.c_str());
}

void CustomJob::JobCompleteCallback(){
    std::cout << "CUSTOMJOB COMPLETED" << std::endl;
}