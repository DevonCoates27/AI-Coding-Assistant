//
// Created by Devon Coates on 9/7/23.
//

#ifndef JOBSYSTEM_JOB_H
#define JOBSYSTEM_JOB_H

#include <mutex>
#include <map>
#include <deque>
#include <vector>
#include <thread>
#include <string>

class Job {
    friend class JobSystem;
    friend class JobWorkerThread;

public:
    Job(int jobType = 0, unsigned long jobChannels = 0xFFFFFFFF, std::string name = "") : m_jobType(jobType), m_jobChannels(jobChannels), m_name(name) {
        static int s_nextJobID = 0;
        m_jobID = s_nextJobID++;
    }

    virtual ~Job(){}

    virtual void Execute() = 0; // This MUST be inherited by the inheritor class - this is now an abstract class
    virtual void JobCompleteCallback(){}; // This CAN be inherited by the inheritor class
    int GetUniqueID()   const { return m_jobID; }
    int GetJobType()    const { return m_jobType; }
    unsigned long GetJobChannels() const { return m_jobChannels; }

private:
    int     m_jobID     = -1;
    int     m_jobType   = -1;

    unsigned long m_jobChannels = 0xFFFFFFFF;
    std::string m_name = "";



};


#endif //JOBSYSTEM_JOB_H
