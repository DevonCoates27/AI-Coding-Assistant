//
// Created by Devon Coates on 9/7/23.
//

#ifndef JOBSYSTEM_COMPILEJOB_H
#define JOBSYSTEM_COMPILEJOB_H

#include "job.h"

class CompileJob : public Job{
public:
    CompileJob(int jobType, unsigned long jobChannels, std::string name) : Job(jobType, jobChannels, name) {};
    ~CompileJob() {};

    std::string output = "";
    int returnCode;

    void Execute();
    void JobCompleteCallback();
};


#endif //JOBSYSTEM_COMPILEJOB_H
