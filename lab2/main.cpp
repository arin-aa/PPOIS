#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include "Application.h"
#include "Cable.h"
#include "Case.h"
#include "CompatibilityChecker.h"
#include "Computer.h"
#include "ComputerExceptions.h"
#include "CPU.h"
#include "DiagnosticService.h"
#include "Driver.h"
#include "File.h"
#include "HDD.h"
#include "IpAddress.h"
#include "Logger.h"
#include "Motherboard.h"
#include "Mouse.h"
#include "NetworkInterface.h"
#include "NVMe.h"
#include "OperatingSystem.h"
#include "Packet.h"
#include "Port.h"
#include "Printer.h"
#include "Process.h"
#include "PSU.h"
#include "RAM.h"
#include "RepairTicket.h"
#include "ReportGenerator.h"
#include "Scanner.h"
#include "Sensor.h"
#include "Server.h"
#include "SSD.h"
#include "SystemBuilder.h"
#include "Technician.h"

const int MENU_WIDTH=50;
const int EXIT_CHOICE=0;
const int RUN_ALL_CHOICE=6;
const int INVALID_CHOICE=-1;
const int WRONG_PASSWORDS=5;
const int LOG_EVENTS=4;
const int LOG_CAPACITY=3;
const int DECIMAL_DIGITS=1;

template<typename Value>
void show(const std::string& call,const Value& result){
    std::cout<<"  "<<call<<" -> "<<std::boolalpha<<std::fixed<<std::setprecision(DECIMAL_DIGITS)<<result<<"\n";
}

void expectError(const std::string& call,const std::function<void()>& action){
    try{
        action();
        show(call,"no error");
    }catch(const ComputerException& error){
        show(call,std::string("BLOCKED: ")+error.what());
    }
}

void showChecks(){
    Motherboard board("LGA1700",2,"ATX");
    CPU intel("LGA1700",8,3.6);
    CPU amd("AM5",8,4.2);
    RAM ddr4(16,"DDR4",3200);
    PSU weakPsu(50,"80+");
    CompatibilityChecker strict(true);
    show("checkSocket(AM5 CPU)",strict.checkSocket(&board,&amd));
    show("checkRam(DDR4), index",strict.checkRam(&board,&ddr4));
    expectError("strict checkPower(50 W PSU)",[&]{strict.checkPower(&weakPsu,&board);});
    show("installCpu(LGA1700 CPU)",board.installCpu(&intel));
    expectError("installCpu(AM5 CPU)",[&]{Motherboard other("LGA1700",1,"ATX");other.installCpu(&amd);});
    intel.runLoad(99);
    show("CPU GHz after runLoad(99)",intel.getFrequencyGhz());
    expectError("overclock(3.0)",[&]{intel.overclock(3.0);});
    ddr4.allocate(8);
    show("RAM used GB after allocate(8)",ddr4.getUsedGb());
    expectError("allocate(16)",[&]{ddr4.allocate(16);});
}

void scenarioBuildComputer(){
    std::cout<<"\n[Scenario 1: building, checking and starting a computer]\n";
    Motherboard board("LGA1700",2,"ATX");
    PSU psu(650,"80+ Gold");
    Case chassis("ATX",350);
    SSD disk(512);
    SystemBuilder builder;
    builder.installMotherboard(&board);
    builder.installPsu(&psu);
    show("build() without a case is empty",builder.build()==nullptr);
    builder.installCase(&chassis);
    std::unique_ptr<Computer> computer=builder.build();
    computer->addStorage(&disk);
    show("totalPowerDraw(), W",computer->totalPowerDraw());
    computer->powerOn();
    show("isOn() after powerOn()",computer->isOn());
    showChecks();
}

void showProcess(OperatingSystem* os,Application* app){
    Process* process=os->startProcess(app);
    show("startProcess(), state",process->getState());
    process->suspend();
    show("suspend(), state",process->getState());
    process->resume();
    show("resume(), state",process->getState());
    show("killProcess(pid)",os->killProcess(process->getPid()));
    show("state after the kill",process->getState());
}

void showSystem(){
    OperatingSystem os("Linux","x86_64","6.1");
    SSD disk(256);
    CPU cpu("AM5",8,4.0);
    Driver rogue("rogue","CPU",false);
    Driver driver("cpu-driver","CPU",true);
    Application editor("Blender","3.6",2000,4096,"KEY-1");
    expectError("boot() before install()",[&]{os.boot();});
    os.install(&disk);
    show("installDriver(unsigned)",os.installDriver(&rogue));
    show("installDriver(signed)",os.installDriver(&driver));
    show("findDriverFor(cpu) is the signed driver",os.findDriverFor(&cpu)==&driver);
    show("boot(), isRunning()",os.boot()&&os.isRunning());
    editor.install(&disk);
    show("disk.getUsedGb() after editor.install()",disk.getUsedGb());
    show("editor.checkLicense(WRONG)",editor.checkLicense("WRONG"));
    showProcess(&os,&editor);
}

void scenarioStorageAndSystem(){
    std::cout<<"\n[Scenario 2: storage devices, operating system and software]\n";
    HDD hdd(1000,7200);
    SSD ssd(256);
    NVMe nvme(512,4);
    hdd.write(200);
    show("hdd.getUsedGb() after write(200)",hdd.getUsedGb());
    show("hdd.erase(500)",hdd.erase(500));
    show("hdd.defragment()",hdd.defragment());
    ssd.write(200);
    expectError("ssd.write(100)",[&]{ssd.write(100);});
    ssd.trim();
    show("ssd.getUsedGb() after trim()",ssd.getUsedGb());
    show("nvme.calcThroughput(), MB/s",nvme.calcThroughput());
    showSystem();
}

void scenarioNetwork(){
    std::cout<<"\n[Scenario 3: network and server]\n";
    IpAddress source("192.168.0.10",24);
    IpAddress target("192.168.0.20",24);
    IpAddress broken("not-an-ip",24);
    Packet packet(&source,&target,512);
    NetworkInterface nic("eth0",1000);
    Server server("web-01",2);
    show("source.isInSameSubnet(target)",source.isInSameSubnet(&target));
    expectError("send() through a down interface",[&]{nic.send(&packet,&target);});
    nic.up();
    show("TTL before send()",packet.getTtl());
    nic.send(&packet,&target);
    show("TTL after send()",packet.getTtl());
    expectError("send() to a malformed address",[&]{nic.send(&packet,&broken);});
    show("server.handleRequest(packet)",server.handleRequest(&packet));
    show("server.handleRequest(nullptr)",server.handleRequest(nullptr));
    server.setupRaid("RAID1");
    show("server.getRaidLevel()",server.getRaidLevel());
}

void showPrinting(){
    Printer printer(0,100);
    Scanner scanner(300);
    std::unique_ptr<File> page=scanner.scan();
    show("scanner.scan(), file",page->getFileName());
    show("print() without paper",printer.print(page.get()));
    printer.refillPaper(10);
    show("print() after refillPaper(10)",printer.print(page.get()));
    show("printer.getPaperLevel()",printer.getPaperLevel());
}

void scenarioPeripherals(){
    std::cout<<"\n[Scenario 4: ports and peripherals]\n";
    Port usbPort("USB");
    Cable usbCable("USB",1.5);
    Cable hdmiCable("HDMI",2.0);
    Mouse mouse(800,3);
    expectError("plug(HDMI cable) into a USB port",[&]{usbPort.plug(&hdmiCable);});
    expectError("plug(USB cable) into a USB port",[&]{usbPort.plug(&usbCable);});
    expectError("mouse.connectTo(nullptr)",[&]{mouse.connectTo(nullptr);});
    show("mouse.connectTo(usbPort)",mouse.connectTo(&usbPort));
    show("usbPort.connectPeripheral(mouse)",usbPort.connectPeripheral(&mouse));
    show("mouse.setDpi(50)",mouse.setDpi(50));
    mouse.setDpi(1600);
    show("mouse.getDpi() after setDpi(1600)",mouse.getDpi());
    showPrinting();
}

void showAuthentication(){
    User user("ivanov","secret");
    show("authenticate(secret)",user.authenticate("secret"));
    for(int attempt=0;attempt<WRONG_PASSWORDS;attempt++){
        user.authenticate("guess");
    }
    show("getFailedAttempts()",user.getFailedAttempts());
    expectError("authenticate(secret) on a locked account",[&]{user.authenticate("secret");});
}

void showServiceTools(){
    Computer pc("diag-pc");
    Sensor alarm("C",0.0);
    Logger logger("INFO",LOG_CAPACITY);
    DiagnosticService diagnostics(&logger);
    ReportGenerator generator("txt","admin");
    File report("report.txt",1,false);
    show("checkTemperature(alarm sensor)",diagnostics.checkTemperature(&pc,&alarm));
    for(int event=1;event<=LOG_EVENTS;event++){
        logger.log("Event "+std::to_string(event));
    }
    show("logger.getEntryCount()",logger.getEntryCount());
    show("saveToFile()",generator.saveToFile(generator.generateReport(&pc),&report));
    show("report.getContent()",report.getContent());
}

void scenarioServiceDesk(){
    std::cout<<"\n[Scenario 5: repairs, access, diagnostics and reports]\n";
    Technician technician("ivanov","secret","hardware",5);
    Computer pc("office-pc");
    SSD disk(512);
    RepairTicket ticket(1,"Disk failure",&pc);
    show("ticket.getStatus()",ticket.getStatus());
    technician.acceptTicket(&ticket);
    show("status after acceptTicket()",ticket.getStatus());
    technician.repair(&pc,&disk);
    show("status after repair()",ticket.getStatus());
    show("escalate() of a closed ticket",ticket.escalate());
    showAuthentication();
    showServiceTools();
}

struct Scenario{
    const char* title;
    void (*run)();
};

const Scenario SCENARIOS[]={
    {"Building, checking and starting a computer",scenarioBuildComputer},
    {"Storage devices, operating system and software",scenarioStorageAndSystem},
    {"Network and server",scenarioNetwork},
    {"Ports and peripherals",scenarioPeripherals},
    {"Repairs, access, diagnostics and reports",scenarioServiceDesk}
};

const int SCENARIO_COUNT=sizeof(SCENARIOS)/sizeof(SCENARIOS[0]);

void showMenu(){
    std::cout<<"\n"<<std::string(MENU_WIDTH,'=')<<"\n  COMPUTER - SCENARIO DEMONSTRATION\n";
    for(int index=0;index<SCENARIO_COUNT;index++){
        std::cout<<"  "<<index+1<<". "<<SCENARIOS[index].title<<"\n";
    }
    std::cout<<"  "<<RUN_ALL_CHOICE<<". Run all scenarios\n  "<<EXIT_CHOICE<<". Exit\nYour choice: ";
}

int parseChoice(const std::string& line){
    try{
        return std::stoi(line);
    }catch(const std::exception&){
        return INVALID_CHOICE;
    }
}

void runChoice(int choice){
    if(choice==RUN_ALL_CHOICE){
        for(const Scenario& scenario:SCENARIOS){
            scenario.run();
        }
    }else if(choice>0 && choice<=SCENARIO_COUNT){
        SCENARIOS[choice-1].run();
    }else if(choice!=EXIT_CHOICE){
        std::cout<<"No such scenario\n";
    }
}

int main(){
    std::string line;
    int choice=INVALID_CHOICE;
    showMenu();
    while(choice!=EXIT_CHOICE && std::getline(std::cin,line)){
        choice=parseChoice(line);
        runChoice(choice);
        if(choice!=EXIT_CHOICE){
            showMenu();
        }
    }
    return 0;
}
