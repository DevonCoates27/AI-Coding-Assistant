#ifndef JOBSYSTEMAPI_JOBSYSTEMAPI_H
#define JOBSYSTEMAPI_JOBSYSTEMAPI_H

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "job.h"
#include "renderjob.h"
#include "subtractjob.h"
#include "jobsystem.h"
#include "compilejob.h"
#include "customjob.h"
#include "promptjob.h"


class jobSystemAPI{
    public:
        jobSystemAPI();
        void createSystem();
        void destroyAllThreads();
        std::string listJobs();
        void createJob(std::string input);
        std::string getStatus(std::string input);
        void destroyJob(std::string input);
        void completeJobs();
        void stopSystem();
        void destroySystem();
        void createThread(std::string input);
        void destroyThread();
        // std::string registerJob();
        void startSystem();
        void waitAllThreads();
        void queueNamedJob(std::string name);

    private:
        JobSystem* js;
};
#endif