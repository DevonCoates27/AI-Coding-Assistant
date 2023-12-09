#include <iostream>
#include <unistd.h>
#include <string>
#include <vector>
#include <fstream>
#include "./JobSystemCode/jobSystemAPI.h"
#include "interpreter.h"
#include "variable.h"

int main(void) {

    std::cout << "Creating Job System and worker threads" << std::endl;

    jobSystemAPI* jsAPI = new jobSystemAPI();

    jsAPI->createThread("{\"uniqueName\": \"Thread1\", \"workerJobChannels\": \"0x0000000F\"}");
    jsAPI->createThread("{\"uniqueName\": \"Thread2\", \"workerJobChannels\": \"0x000000F0\"}");
    jsAPI->createThread("{\"uniqueName\": \"Thread3\", \"workerJobChannels\": \"0x00000F00\"}");
    jsAPI->createThread("{\"uniqueName\": \"Thread4\", \"workerJobChannels\": \"0x0000F000\"}");
    jsAPI->createThread("{\"uniqueName\": \"Thread5\", \"workerJobChannels\": \"0x000F0000\"}");
    jsAPI->createThread("{\"uniqueName\": \"Thread6\", \"workerJobChannels\": \"0x00F00000\"}");
    jsAPI->createThread("{\"uniqueName\": \"Thread7\", \"workerJobChannels\": \"0x0F000000\"}");
    jsAPI->createThread("{\"uniqueName\": \"Thread8\", \"workerJobChannels\": \"0xF0000000\"}");

    std::cout << "List of available jobs:" << std::endl;
    std::cout << jsAPI->listJobs();

    bool running = true, assistant = false, started = false;
    std::string command, func, keyword, jobJSON, jobName, channels, output, id, variableInfo, variableName, parseFunc, buffer, buffer2, answer;

    while(running){
        std::cout << "Enter a command (create, destroy, continue, parseDot - or - startCodeAssistant): ";
        std::cin >> command;
        if(command == "startCodeAssistant"){
            std::cout << "Would you like to use flowscript or a more reliable auto loop (flowscript/loop)?" << std::endl;
            std::cin >> answer;
            if(answer == "loop"){
                jsAPI->createJob("{\"JobType\": \"compileJob\", \"JobChannels\": \"0x0000000F\", \"JobName\": \"A\"}");
                jsAPI->startSystem();
                jsAPI->queueNamedJob("A");
                jsAPI->waitAllThreads();
                sleep(2);
                jsAPI->completeJobs();
                sleep(2);

                std::ifstream input;
                input.open("Data/errors.json");
                std::string buffer;
                int lineCount = 0;
                while(!input.eof()){
                    getline(input, buffer);
                    lineCount++;
                }

                while(lineCount >= 7){
                    jsAPI->createJob("{\"JobType\": \"promptJob\", \"JobChannels\": \"0x0000000F\", \"JobName\": \"B\"}");
                    jsAPI->queueNamedJob("B");
                    jsAPI->waitAllThreads();
                    jsAPI->completeJobs();
                    sleep(1);
                    jsAPI->createJob("{\"JobType\": \"customJob\", \"JobChannels\": \"0x0000000F\", \"JobName\": \"C\"}");
                    jsAPI->queueNamedJob("C");
                    jsAPI->waitAllThreads();
                    jsAPI->completeJobs();
                    sleep(1);
                    jsAPI->createJob("{\"JobType\": \"compileJob\", \"JobChannels\": \"0x0000000F\", \"JobName\": \"D\"}");
                    jsAPI->queueNamedJob("D");
                    jsAPI->waitAllThreads();
                    jsAPI->completeJobs();
                    sleep(1);
                    input.close();
                    input.open("Data/errors.json");
                    buffer = "";
                    lineCount = 0;
                    while(!input.eof()){
                        getline(input, buffer);
                        lineCount++;
                    }
                }
                std::cout << "Agent Finished" << std::endl;
            }else if(answer == "flowscript"){
                command = "parseDot";
                assistant = true;
            }
        }
        if(command == "parseDot"){
            std::cout << "Line by line interpreter beginning!!\n\n" << std::endl;
            std::vector<Variable*> variables;
            Interpreter inter;
            std::ifstream input;
            if(assistant){input.open("Code/codeAssistantDot.txt");}
            else{input.open("Code/dotMain.txt");}
            if(!input.is_open())
                std::cout << "Dot file failed to open" << std::endl;
            else
                std::cout << "File Opened\n\n" << std::endl;
            
            getline(input, func);
            std::stringstream in(func);

            while(!input.eof()){
                getline(input, func);
                parseFunc = inter.getFunction(func);

                std::stringstream in(parseFunc);

                getline(in, keyword, ':');
                if(keyword == "renderJob"){
                    getline(in, jobJSON);
                    jsAPI->createJob(jobJSON);
                }else if(keyword == "subtractJob"){
                    getline(in, jobJSON);
                    jsAPI->createJob(jobJSON);
                }else if(keyword == "compileJob"){
                    getline(in, jobJSON);
                    jsAPI->createJob(jobJSON);
                }else if(keyword == "customJob"){
                    getline(in, jobJSON);
                    jsAPI->createJob(jobJSON);
                }else if(keyword == "promptJob"){
                    getline(in, jobJSON);
                    jsAPI->createJob(jobJSON);
                }else if(keyword == "string"){
                    getline(in, variableInfo, ',');
                    getline(in, variableName);
                    Variable* newVar = new Variable(variableName, "string", variableInfo);
                    variables.push_back(newVar);
                    std::cout << "Added a string named \"" << variableName << "\" with data: " << variableInfo << std::endl;
                }else if(keyword == "int"){
                    getline(in, variableInfo, ',');
                    getline(in, variableName);
                    Variable* newVar = new Variable(variableName, "int", variableInfo);
                    variables.push_back(newVar);
                    std::cout << "Added an int named \"" << variableName << "\" with data: " << variableInfo << std::endl;
                }else if(keyword == "double"){
                    getline(in, variableInfo, ',');
                    getline(in, variableName);
                    Variable* newVar = new Variable(variableName, "double", variableInfo);
                    variables.push_back(newVar);
                    std::cout << "Added a double named \"" << variableName << "\" with data: " << variableInfo << std::endl;
                }else if(keyword == "ulong"){
                    getline(in, variableInfo, ',');
                    getline(in, variableName);
                    Variable* newVar = new Variable(variableName, "ulong", variableInfo);
                    variables.push_back(newVar);
                    std::cout << "Added a ulong named \"" << variableName << "\" with data: " << variableInfo << std::endl;
                }else if(keyword == "bool"){
                    getline(in, variableInfo, ',');
                    getline(in, variableName);
                    Variable* newVar = new Variable(variableName, "bool", variableInfo);
                    variables.push_back(newVar);
                    std::cout << "Added a bool named \"" << variableName << "\" with data: " << variableInfo << std::endl;
                }else if(keyword == "char"){
                    getline(in, variableInfo, ',');
                    getline(in, variableName);
                    Variable* newVar = new Variable(variableName, "char", variableInfo);
                    variables.push_back(newVar);
                    std::cout << "Added a char named \"" << variableName << "\" with data: " << variableInfo << std::endl;
                }else if(keyword == "char*"){
                    getline(in, variableInfo, ',');
                    getline(in, variableName);
                    Variable* newVar = new Variable(variableName, "char*", variableInfo);
                    variables.push_back(newVar);
                    std::cout << "Added a char* named \"" << variableName << "\" with data: " << variableInfo << std::endl;
                }else if(keyword == "dependency"){
                    getline(in, buffer, '-');
                    getline(in, buffer2);
                    if(!started){
                        jsAPI->startSystem();
                        std::cout << "\nSYSTEM STARTED" << std::endl;
                    }
                    jsAPI->queueNamedJob(buffer);
                    std::cout << "QUEUED " << buffer << std::endl;
                    jsAPI->waitAllThreads();
                    jsAPI->completeJobs();
                    sleep(1);
                    jsAPI->queueNamedJob(buffer2);
                    std::cout << "QUEUED " << buffer2 << std::endl;
                    jsAPI->waitAllThreads();
                    jsAPI->completeJobs();
                    sleep(1);
                }else if(keyword == "Nothing found")
                    std::cout << "Blank line or no command found" << std::endl;
                else
                    std::cerr << "SYNTAX ERROR (no variable/jobtype match or unavailable dependency)";
            }
            sleep(5);
            return 0;
        }else if(command == "create"){
            while(jobName != "renderJob" && jobName != "subtractJob" && jobName != "compileJob" && jobName != "customJob"){
                std::cout << "Enter the type of the job you wish to create: ";
                std::cin >> jobName;
                if(jobName != "renderJob" && jobName != "subtractJob" && jobName != "compileJob" && jobName != "customJob"){
                    std::cout << "Improper job type" << std::endl;
                }
            }
            std::cout << "\nEnter the job channels: ";
            std::cin >> channels;
            std::cout << std::endl;
            output = "{\"JobType\": \"" + jobName + "\", \"JobChannels\": \"" + channels + "\", \"JobName\": \"null\"}";
            jsAPI->createJob(output);
        }
        else if(command == "destroy"){
            std::cout << "\nEnter the ID of the job you would like to destroy: ";
            std::cin >> id;
            jsAPI->destroyJob("{\"JobID\": \"" + id + "\"}");
        }
        else if(command == "continue"){
            running = false;
        }
        else{
            std::cout << "\nInvalid command, try again: ";
        }
    }

    running = true;
    while(running){
        std::cout << "Enter a command (startSystem, stopSystem, completeJobs, listJobs, createJob): ";
        std::cin >> command;

        if(command == "startSystem"){
            jsAPI->startSystem();
            std::cout << "Started System." << std::endl;
        }
        else if(command == "stopSystem")
            running = false;
        // else if(command == "destroyThreads")
        //     jsAPI->destroyAllThreads();
        // else if(command == "destroySystem") {
        //     jsAPI->destroySystem();
        //     running = false;
        // }
        // else if(command == "destroyJob"){
        //     std::string id;
        //     std::cout << "\nEnter the ID of the job you would like to destroy: ";
        //     std::cin >> id;
        //     jsAPI->destroyJob("{\"JobType\": \"" + id + "\"}");
        // }
        else if(command == "completeJobs"){
            jsAPI->completeJobs();
        }
        // else if(command == "getJobStatus"){
        //     std::string num;
        //     std::cout << "Enter job ID: ";
        //     std::cin >> num;
        //     std::cout << jsAPI->getStatus("{\"jobID\": \"" + num + "\"}");
        // }
        else if(command == "listJobs"){
            std::cout << "Listing all available jobs:" << std::endl;
            std::cout << jsAPI->listJobs();
        }
        else if(command == "createJob"){
            std::cout << "Enter the type of the job you wish to create: ";
            std::string jobName, channels, type, output;
            std::cin >> jobName;
            std::cout << "\nEnter the job channels: ";
            std::cin >> channels;
            output = "{\"JobName\": \"" + jobName + "\", \"JobChannels\": \"" + channels + "\"}";
            jsAPI->createJob(output);
        }
        else{
            std::cout << "Invalid Command" << std::endl;
        }
    }
    return 0;
}