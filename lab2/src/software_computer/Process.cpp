#include "Process.h"
#include "Application.h"

const char* const NEW="new";
const char* const RUNNING="running";
const char* const STOPPED="stopped";

Process::Process():ramUsageMb(0),state(NEW),app(nullptr){}

Process::Process(Application* app):ramUsageMb(0),state(NEW),app(app){}

int Process::start(int freeRamMb){
    ramUsageMb=freeRamMb-app->launch(freeRamMb);
    state=RUNNING;
    return ramUsageMb;
}

int Process::terminate(){
    int freed=state==RUNNING?ramUsageMb:0;
    ramUsageMb=0;
    state=STOPPED;
    return freed;
}
