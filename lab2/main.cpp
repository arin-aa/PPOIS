/**
 * @file main.cpp
 * @brief Console user interface for the computer hardware accounting system.
 */

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

#include "Application.h"
#include "Cable.h"
#include "Case.h"
#include "CompatibilityChecker.h"
#include "Computer.h"
#include "ComputerExceptions.h"
#include "CPU.h"
#include "Driver.h"
#include "Fan.h"
#include "File.h"
#include "Folder.h"
#include "HDD.h"
#include "Inventory.h"
#include "IpAddress.h"
#include "Motherboard.h"
#include "Mouse.h"
#include "NetworkInterface.h"
#include "OperatingSystem.h"
#include "Packet.h"
#include "Port.h"
#include "PowerConnector.h"
#include "Printer.h"
#include "Process.h"
#include "PSU.h"
#include "Radiator.h"
#include "RAM.h"
#include "RepairTicket.h"
#include "Server.h"
#include "SSD.h"
#include "SystemBuilder.h"
#include "Technician.h"

using namespace std;

//Maximum number of characters ignored in the input stream on error.
const int MAX_IGNOR=100000;
const int ACTION_WIDTH=50;///<Width of the action name column.
const int RESULT_WIDTH=44;///<Width of the result column.

/**
 * @brief Requests an integer from the user with input validation.
 * @param line Text displayed before the expected number input.
 * @return choice The number entered by the user.
 * 
 * On invalid input (e.g., string, letters, spaces, or other values),
 * clears the input stream and repeats the request until a correct value is obtained.
 */
int readChoice(const string& line){
    int choice;
    while(true){
        cout<<line;
        if(cin>>choice){
            cin.clear(); cin.ignore(MAX_IGNOR,'\n');
            return choice; 
        }
        cin.clear(); cin.ignore(MAX_IGNOR,'\n');
        cout<<"Invalid input. Try again.\n";
    }
}

/**
 * @brief Prints the scenario title and the table header.
 * @param number Scenario sequence number.
 * @param name Scenario name.
 */
void title(int number,const string& name){
    cout<<"\n=== "<<number<<". "<<name<<" ===\n"<<left<<setw(ACTION_WIDTH)<<"Action"<<"Result\n";
    cout<<string(ACTION_WIDTH-2,'-')<<"  "<<string(RESULT_WIDTH,'-')<<"\n";
}

/**
 * @brief Prints a single table row with alignment.
 * @param action Description of the action.
 * @param result Result of execution.
 */
void row(const string& action,const string& result){
    cout<<left<<setw(ACTION_WIDTH)<<action<<result<<"\n";
}

/**
 * @brief Outputs a numeric or boolean result.
 * @tparam Value Type of the passed value (int, double, bool).
 * @param action Description of the action.
 * @param value The value itself.
 * @param unit Unit of measurement (empty string by default).
 */
template<typename Value>
void report(const string& action,const Value& value,const string& unit=""){
    ostringstream text;
    text<<boolalpha<<fixed<<setprecision(1)<<value;
    row(action,"done, "+text.str()+unit);
}

/**
 * @brief Executes an action and catches possible exceptions.
 * @tparam Action Type of the called lambda function.
 * @param action Description of the action.
 * @param run Lambda function with the code to execute.
 */
template<typename Action>
void attempt(const string& action,Action run){
    try{
        run();
        row(action,"done");
    }catch(const ComputerException& error){
        row(action,string("ERROR: ")+error.what());
    }
}

/**
 * @brief Scenario 1: Building a PC and checking CPU compatibility with the motherboard.
 */
void scenarioBuild(){
    title(1,"Building a computer");
    Motherboard board("LGA1700",1);
    CPU intel("LGA1700",8,3.6);
    CPU amd("AM5",8,4.2);
    RAM ram(16,3200);
    PSU psu(650,"80+ Gold");
    Computer pc("office-pc");
    attempt("Install an AMD (AM5) CPU on an LGA1700 board",[&]{board.installCpu(&amd);});
    attempt("Install an Intel (LGA1700) CPU",[&]{board.installCpu(&intel);});
    attempt("Install a second RAM module into one slot",[&]{board.installRam(&ram);board.installRam(&ram);});
    attempt("Power on before assembling",[&]{pc.powerOn();});
    pc.assemble(&board,&psu);
    attempt("Power on the assembled computer",[&]{pc.powerOn();});
    report("Power reserve of the PSU",pc.powerReserve()," W");
}

/**
 * @brief Scenario 2: Calculating PSU wattage, cooler operation, and power connectors.
 */
void scenarioPower(){
    title(2,"Power and cooling");
    CompatibilityChecker checker(true,100);
    SystemBuilder builder(1000,&checker);
    Fan fan1(120,1000);
    Fan fan2(140,800);
    Case chassis(1);
    Radiator radiator(240,300);
    PowerConnector connector(8);
    builder.addPart(105,500);
    report("Recommended PSU for the chosen parts",builder.recommendedPsu()," W");
    attempt("Check a 150 W PSU in strict mode",[&]{builder.powerMargin(150);});
    attempt("Add a part for 900 to a budget of 1000",[&]{builder.addPart(300,900);});
    chassis.addFan(&fan1);
    attempt("Mount a second fan into a one-fan case",[&]{chassis.addFan(&fan2);});
    report("Case airflow",chassis.totalAirflow()," units");
    report("Refill the radiator with 1000 ml",radiator.refill(1000)," ml");
    attempt("Plug the 8-pin power connector twice",[&]{connector.attach();connector.attach();});
}

/**
 * @brief Scenario 3: Working with storage devices and the file system.
 */
void scenarioStorage(){
    title(3,"Storage devices and files");
    SSD ssd(256);
    HDD hdd(1000,7200,40);
    File notes("notes.txt",10,false);
    File image("disk.iso",20,false);
    Folder folder(15);
    attempt("Write 200 GB and then 100 GB to a 256 GB SSD",[&]{ssd.write(200);ssd.write(100);});
    report("Trim the SSD, freed",ssd.trim()," GB");
    report("Defragment the HDD, it takes",hdd.defragment()," min");
    attempt("Put a 10 MB file into a 15 MB folder",[&]{folder.addFile(&notes);});
    attempt("Put a 20 MB file into the same folder",[&]{folder.addFile(&image);});
}

/**
 * @brief Scenario 4: Installing an OS and managing processes.
 */
void scenarioSoftware(){
    title(4,"Operating system and programs");
    OperatingSystem os("Linux",5000);
    OperatingSystem legacy("Legacy",100);
    Driver rogue("rogue","GPU",false);
    Application editor("Blender",2000,4096,"KEY-1");
    Process process(&editor);
    os.install(10);
    legacy.install(10);
    legacy.addDriver(&rogue);
    os.boot();
    attempt("Boot an OS that has an unsigned driver",[&]{legacy.boot();});
    attempt("Start Blender before installing it",[&]{os.startProcess(&process,8192);});
    report("Install Blender, it needs",editor.install(50)," GB");
    int pid=os.startProcess(&process,8192);
    report("Start Blender, process id",pid);
    report("Stop the process, freed",os.killProcess(pid)," MB");
}

/**
 * @brief Scenario 5: Network configuration and server operation.
 */
void scenarioNetwork(){
    title(5,"Network and server");
    IpAddress source("192.168.0.10",24);
    IpAddress broken("not-an-ip",24);
    NetworkInterface nic(1000);
    Packet packet(&source,"192.168.0.20",512,1);
    attempt("Connect the card to the address not-an-ip",[&]{nic.connect(&broken);});
    attempt("Send data through a disconnected card",[&]{nic.transmitNs(800);});
    nic.connect(&source);
    report("Is the packet inside the local subnet",packet.isLocal());
    Server server("web-01",2,&nic);
    report("Server handles a request in",server.handleRequest(&packet)," ns");
    attempt("Server handles the same packet again",[&]{server.handleRequest(&packet);});
    report("Set RAID1, usable disk space",server.configureRaid("RAID1"),"%");
}

/**
 * @brief Scenario 6: Connecting peripherals via ports and cables.
 */
void scenarioPeripherals(){
    title(6,"Ports, cables and peripherals");
    Port usb("USB",480);
    Cable usbCable("USB",1.5,500);
    Cable hdmiCable("HDMI",2.0,1000);
    Mouse mouse(800);
    Printer printer(0,100);
    File page("page.txt",1,false);
    attempt("Plug an HDMI cable into a USB port",[&]{usb.plug(&hdmiCable);});
    usb.plug(&usbCable);
    attempt("Click the mouse before connecting it",[&]{mouse.click();});
    mouse.connectTo(&usb);
    printer.connectTo(&usb);
    report("Click the mouse, total clicks",mouse.click());
    attempt("Set the mouse to 50 DPI",[&]{mouse.changeDpi(50);});
    attempt("Print a page with an empty paper tray",[&]{printer.print(&page);});
    printer.loadPaper(10);
    report("Print a page, pages printed so far",printer.print(&page));
}

/**
 * @brief Scenario 7: Service center operation and authentication.
 */
void scenarioRepair(){
    title(7,"Repairs and access");
    Technician tech("ivanov","secret1","hardware",5);
    Computer pc("desk-pc");
    RepairTicket ticket("No video signal",&pc);
    Inventory stock("North warehouse",1);
    Fan spare(120,900);
    attempt("Close a ticket nobody works on",[&]{ticket.close(2);});
    ticket.assign(&tech);
    stock.addItem(&spare);
    attempt("Order a GPU that is not in stock",[&]{tech.orderPart(&stock,"GPU");});
    attempt("Order the Noctua fan from the stock",[&]{tech.orderPart(&stock,"Noctua");});
    report("Close the ticket after 3 hours, cost",ticket.close(3));
    attempt("Wrong password 3 times, then the right one",[&]{for(int i=0;i<3;i++){tech.authenticate("guess");}tech.authenticate("secret1");});
}

/**
 * @brief Program entry point
 * @return Program exit code.
 * 
 * Displays the main menu, prompting the user to choose one of 7 scenarios 
 * or exit the program. Handles invalid input.
 */
int main(){
    while(true){
        cout<<"\nMenu\n";
        cout<<"1 - Computer assembly and compatibility.\n";
        cout<<"2 - Power and cooling.\n";
        cout<<"3 - Storage devices and files.\n";
        cout<<"4 - Operating system and programs.\n";
        cout<<"5 - Network and server.\n";
        cout<<"6 - Peripherals and ports.\n";
        cout<<"7 - Repair and access.\n";
        cout<<"0 - Exit.\n";
        
        int choice = readChoice("Your choice: "); 
        cout<<endl;

        switch(choice){
            case 1: scenarioBuild(); break;
            case 2: scenarioPower(); break;
            case 3: scenarioStorage(); break;
            case 4: scenarioSoftware(); break;
            case 5: scenarioNetwork(); break;
            case 6: scenarioPeripherals(); break;
            case 7: scenarioRepair(); break;
            case 0:
                cout<<"Exit.\n";
                return 0;
            default:
                cout<<"Invalid choice.\n";
        }
    }
    return 0;
}