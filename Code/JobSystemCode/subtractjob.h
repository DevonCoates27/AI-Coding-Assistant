#ifndef JOBSYSTEM_SUBTRACTJOB_H
#define JOBSYSTEM_SUBTRACTJOB_H

#include <vector>
#include "job.h"


class SubtractJob : public Job {
    public:
        SubtractJob(unsigned long jobChannels, int jobType, std::string name) : Job(jobChannels, jobType, name) {};
        ~SubtractJob(){};

        std::vector<int> data;
        void Execute();
        void JobCompleteCallback();
};


#endif //JOBSYSTEM_RENDERJOB_H