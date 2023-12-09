#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

class Interpreter{
private:

public:
    Interpreter();
    Interpreter(const Interpreter& obj);


    std::string getFunction(std::string func);

};