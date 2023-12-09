//
// Created by Devon Coates on 9/7/23.
//

#include "promptjob.h"
#include <iostream>
#include <fstream>

void PromptJob::Execute(){ // This job is taking the errors and source code to make a prompt for openai
    std::cout << "Starting to compile data to make prompt\n\n" << std::endl;

    prompt = "You are going to roleplay as a professional C++ developer. I will give you a file with errors in it as well as a JSON file with a list of those errors. Your job is to correct the errors and add any comments to the code of what you changed. You will then provide the code alone with no additional text.\n\nRaw code:\n";

    /***********************READ IN SOURCE CODE*****************************/
        std::ifstream input;
        input.open("Code/JobSystemCode/CodeToTest/file1.cpp");

        if(!input.is_open()){
            std::cerr << "SOURCE CODE FILE FAILED TO OPEN";
        }

        std::string temp;
        while(!input.eof()){
            getline(input, temp);
            prompt += temp + "\n";
        }

        input.close();
    /***********************READ IN SOURCE CODE*****************************/

    prompt += "\n\nErrors Json:\n";

    /***********************READ IN ERRORS JSON*****************************/
        std::ifstream input2;
        input2.open("Data/errors.json");

        if(!input2.is_open()){
            std::cerr << "ERRORS JSON FILE FAILED TO OPEN";
        }

        while(!input2.eof()){
            getline(input2, temp);
            prompt += temp + "\n";
        }

        input2.close();
    /***********************READ IN ERRORS JSON*****************************/
}

void PromptJob::JobCompleteCallback(){ // This outputs the prompt to prompt.txt

    /***********************OUTPUT TO PROMPT.TXT***************************/
        std::ofstream output;
        output.open("Data/prompt.txt");

        if(!output.is_open()){
            std::cerr << "ERRORS JSON FILE FAILED TO OPEN";
        }

        output << prompt;
    /***********************OUTPUT TO PROMPT.TXT***************************/

    std::cout << "PROMPTJOB COMPLETED" << std::endl;
}