//
// Created by Devon Coates on 9/7/23.
//

#ifndef JOBSYSTEM_RENDERJOB_H
#define JOBSYSTEM_RENDERJOB_H

#include <vector>
#include "job.h"


class RenderJob : public Job {
    public:
        RenderJob(int jobType, unsigned long jobChannels, std::string name) : Job(jobType, jobChannels, name) {};
        ~RenderJob(){};

        std::vector<int> data;
        void Execute();
        void JobCompleteCallback();
};


#endif //JOBSYSTEM_RENDERJOB_H
