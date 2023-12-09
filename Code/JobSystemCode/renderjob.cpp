//
// Created by Devon Coates on 9/7/23.
//

#include "renderjob.h"
#include <iostream>

void RenderJob::Execute(){ // This job is just doing random stuff as an example
    std::cout << "Render Job has been executed." << std::endl;
}

void RenderJob::JobCompleteCallback(){ // This just prints the sum after execute finds the sum
    std::cout << "Render Job callback completed." << std::endl;
}