#include "Process.h"
#include "Application.h"

Process::Process():pid(0),ramUsageMb(0),state("terminated"),app(nullptr){}

Process::Process(int pid,Application* app,int ramUsageMb):pid(pid),ramUsageMb(ramUsageMb),state("running"),app(app){}

void Process::suspend(){
    if(state=="terminated"){
        return;
    }
    state="suspended";
}

void Process::resume(){
    if(state!="suspended"){
        return;
    }
    state="running";
}

void Process::terminate(){
    state="terminated";
    ramUsageMb=0;
}