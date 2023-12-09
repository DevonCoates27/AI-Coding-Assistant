//
// Created by Devon Coates on 9/7/23.
//

#ifndef JOBSYSTEM_PROMPTJOB_H
#define JOBSYSTEM_PROMPTJOB_H

#include "job.h"


class PromptJob : public Job {
    public:
        PromptJob(int jobType, unsigned long jobChannels, std::string name) : Job(jobType, jobChannels, name) {};
        ~PromptJob(){};

        void Execute();
        void JobCompleteCallback();

    private:
        std::string prompt = "";
};


#endif //JOBSYSTEM_PROMPTJOB_H
