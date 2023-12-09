#ifndef JOBSYSTEM_CUSTOMJOB_H
#define JOBSYSTEM_CUSTOMJOB_H

#include "job.h"

class CustomJob : public Job{
public:
    CustomJob(int jobType, unsigned long jobChannels, std::string name) : Job(jobType, jobChannels, name) {};
    ~CustomJob() {};

    void Execute();
    void JobCompleteCallback();
};


#endif //JOBSYSTEM_COMPILEJOB_H