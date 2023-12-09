#include "subtractjob.h"
#include <iostream>

void SubtractJob::Execute(){ // This job is just doing random stuff as an example
    std::cout << "Subtract Job execute completed." << std::endl;
}

void SubtractJob::JobCompleteCallback(){ // This just prints the sum after execute finds the sum
    std::cout << "Subtract Job callback completed." << std::endl;
}