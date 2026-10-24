#include "Process.h"
#include "Application.h"

const char* const STATE_RUNNING="running";
const char* const STATE_SUSPENDED="suspended";
const char* const STATE_TERMINATED="terminated";

Process::Process():pid(0),ramUsageMb(0),state(STATE_TERMINATED),app(nullptr){}

Process::Process(int pid,Application* app,int ramUsageMb):pid(pid),ramUsageMb(ramUsageMb),state(STATE_RUNNING),app(app){}

void Process::suspend(){
    if(state==STATE_TERMINATED){
        return;
    }
    state=STATE_SUSPENDED;
}

void Process::resume(){
    if(state!=STATE_SUSPENDED){
        return;
    }
    state=STATE_RUNNING;
}

void Process::terminate(){
    state=STATE_TERMINATED;
    ramUsageMb=0;
}

std::string Process::getState(){
    return state;
}

int Process::getPid(){
    return pid;
}
