#include <iostream>
#include <signal.h>
#include <cstring>
#include <zconf.h>

#include "weederServer.h"

using namespace std;

int quit = 0;

void handle_signal(int signal)
{
    quit = 1;
}


int main(int argc, const char* argv[] ) {


    cout << "Weeder IoT Server v0.1" << endl;


    struct sigaction sa;
    sigfillset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handle_signal;
    sigaction(SIGINT, &sa, NULL);
    cout << "Press Ctrl-C to quit...." << endl;
    WeederIoTServer server;
    //string log_file;

    if(argc>1) {
        if(!strcmp(argv[1], "--show")) {
            cout << "Show data from sensors:" << endl;
            server.showSensors();
            return 0;
        } else if(!strcmp(argv[1], "--get") && argc > 2) {
            int pin_num = atoi(argv[2]);
            cout << "Raw data from PIN: " << pin_num << endl;
            cout << "\tValue: " << server.getData(pin_num) << endl;
            return 0;
        } if(!strcmp(argv[1], "--log") && argc > 2) {
            server.setLog(argv[2]);
        } else {
            cout << "Usage:" << endl;
            cout << "\tweeder --show            To show current data from sensors" << endl;
            cout << "\tweeder --get io_number   To show raw data from pin number: io_number" << endl;
            return 1;
        }
    }

    do
    {
        usleep(2000000);
    }
    while (quit != 1);
    return 0;

}