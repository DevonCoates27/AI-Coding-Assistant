#include "jobSystemAPI.h"

jobSystemAPI::jobSystemAPI(){
    createSystem();
}
void jobSystemAPI::createSystem(){
    js = JobSystem::CreateOrGet();
}
void jobSystemAPI::startSystem(){
    js->startAllThreads();
}
void jobSystemAPI::destroyAllThreads(){
    js->destroyAllThreads();
}
std::string jobSystemAPI::listJobs(){
    std::ifstream in;
    in.open("Data/jobs.txt");
    if(!in.is_open()){
        std::cout << "Failed to open jobs file" << std::endl;
    }
    std::string job, list;
    int i = 1;
    std::getline(in, job);
    while(!in.eof()){
        if(i != 1)
            list += ", ";
        list += job;
        i++;
        std::getline(in, job);
    }
    list += ".\n";
    return list;
}
void jobSystemAPI::createJob(std::string input){
    std::istringstream ss(input);
    std::string buffer, uniqueIdentifier, jobChannels, jobName;
    std::getline(ss, buffer, '"');
    std::getline(ss, buffer, '"');
    std::getline(ss, buffer, '"');
    std::getline(ss, uniqueIdentifier, '"');
    std::getline(ss, buffer, '"');
    std::getline(ss, buffer, '"');
    std::getline(ss, buffer, '"');
    std::getline(ss, jobChannels, '"');
    std::getline(ss, buffer, '"');
    std::getline(ss, buffer, '"');
    std::getline(ss, buffer, '"');
    std::getline(ss, jobName, '"');
    const char* jobType = uniqueIdentifier.c_str();
    unsigned long channels = std::stoul(jobChannels, 0, 16);
    js->createJob(jobType, channels, jobName);
}
std::string jobSystemAPI::getStatus(std::string input){
    std::string buffer, jobID;
    std::istringstream ss(input);
    std::getline(ss, buffer, '"');
    std::getline(ss, buffer, '"');
    std::getline(ss, buffer, '"');
    std::getline(ss, buffer, '"');
    std::string output;
    output = "{\"JobID\": " +buffer+ ", ";
    int id = std::stoi(jobID);
    int status = (int)js->GetJobStatus(id);
    if(status == 0)
        output += "\"JobStatus\": \"NEVER_SEEN\"}";
    else if(status == 1)
        output += "\"JobStatus\": \"QUEUED\"}";
    else if(status == 2)
        output += "\"JobStatus\": \"RUNNING\"}";
    else if(status == 3)
        output += "\"JobStatus\": \"COMPLETED\"}";
    else if(status == 4)
        output += "\"JobStatus\": \"RETIRED\"}";
    return output;

}
void jobSystemAPI::destroyJob(std::string input){
    std::istringstream ss(input);
    std::string buffer, id;
    int idNum;
    std::getline(ss, buffer, '"');
    std::getline(ss, buffer, '"');
    std::getline(ss, buffer, '"');
    std::getline(ss, id, '"');
    idNum = std::stoi(id);
    js->destroyJob(idNum);
}
void jobSystemAPI::completeJobs(){
    js->FinishCompletedJobs();
}
void jobSystemAPI::stopSystem(){
    js->FinishCompletedJobs();
    js->destroyAllThreads();
    js->Destroy();
}
void jobSystemAPI::destroySystem(){

}
void jobSystemAPI::createThread(std::string input){
    std::istringstream ss(input);
    std::string buffer, name, channels;
    std::getline(ss, buffer, '"'); // buffer = "{"
    std::getline(ss, buffer, '"'); // buffer = "uniqueName"
    std::getline(ss, buffer, '"'); // buffer = " :"
    std::getline(ss, name, '"'); // name = name
    std::getline(ss, buffer, '"');
    std::getline(ss, buffer, '"');
    std::getline(ss, buffer, '"');
    std::getline(ss, channels, '"');
    const char* uniqueName = name.c_str();
    unsigned long workerChannels = std::stoul(channels, 0, 16);
    // std::cout << workerChannels << std::endl;
    js->CreateWorkerThread(uniqueName, workerChannels);
}
void jobSystemAPI::destroyThread(){

}

void jobSystemAPI::waitAllThreads(){
    js->waitAllJobs();
}

void jobSystemAPI::queueNamedJob(std::string name){
    js->queueNamedJob(name);
}