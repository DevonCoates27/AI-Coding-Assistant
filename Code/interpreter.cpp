#include "interpreter.h"

Interpreter::Interpreter(){}

Interpreter::Interpreter(const Interpreter& obj){}

std::string Interpreter::getFunction(std::string func){

    /*
        Variable definitions:
            entry = first thing read
            shape = shape
            label = label
            line = full dot language line (reads one line at a time)
            finalFunction = the final function returned in format "Function keyword:parameters"
            buffer = buffer for parsing
            type = jobType
            channels = jobChannels

        Section descriptions:
            Define different variables
            Read an entire line and prep it to be parsed
            Read the line seperating by expected characters
            If the line is not defining something new, set up dependency and return the function
            Get the shape
            Depending on the shape, return a job definition in JSON format or return a variable's definition
            End program
    */

    std::string entry, shape, label, line, whiteLine, finalFunction, buffer, type, channels, varName;    //Initialize variables
    char c;
    std::string dependencyLHS = " ";
    std::string dependencyRHS = " ";

    std::stringstream whiteLineParser(func);                           //create stringstream for entire line

    while(!whiteLineParser.eof()){                                          //Remove whitespace
        whiteLineParser >> c;
        if (!std::isspace(c)) {
            line += c;
        }
    }

    std::stringstream lineParser(line);                                     //Create stringstream for line with no whitespace

    getline(lineParser, entry, '[');                                    //read keyword
    if(lineParser.eof()){
        std::stringstream newParser(line);
        getline(newParser, dependencyLHS, '-');
        if(newParser.eof())
            return "Nothing found";

        getline(newParser, dependencyRHS, '>');
        getline(newParser, dependencyRHS, ';');
        finalFunction = "dependency:" + dependencyLHS + "-" + dependencyRHS;       //Make final function with format "function:parameter-parameter"
        return finalFunction;
    }

    getline(lineParser, buffer, '=');                               //prep to read keyword
    getline(lineParser, shape, ',');                                //read shape
        
    if(shape == "diamond"){
        getline(lineParser, buffer, '\"');                          //prep to read keyword
        getline(lineParser, label, ',');                            //read variable data
        getline(lineParser, varName, '\"');                         //read variable data
        finalFunction = entry + ":" + label + "," + varName;
        // std::cout << finalFunction << std::endl;
        return finalFunction;
    }else if(shape == "circle"){
        getline(lineParser, buffer, '\"');                          //prep to read keyword
        getline(lineParser, type, ',');                             //read job type "renderJob", "subtractJob", etc...
        getline(lineParser, channels, '\"');                        //read channels
        finalFunction = type + ":{\"JobType\": \"" + type + "\", \"JobChannels\": \"" + channels + "\", \"JobName\": \"" + entry + "\"}";
        // std::cout << finalFunction << std::endl;
        return finalFunction;
    }
    return finalFunction;
}


/*TO DO LIST:

    Set up syntax for reading loops
    Get rid of white space before entry
    Set up an interpreter in main
    Read through the entire file and run the getFunction function for each line
    Parse the finalFunction in main to run functions

*/