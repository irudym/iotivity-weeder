#include <iostream>
#include <signal.h>

#include "weederServer.h"

using namespace std;

int quit = 0;

void handle_signal(int signal)
{
    quit = 1;
}


int main() {
    cout << "Weeder IoT Server v0.1" << endl;

    struct sigaction sa;
    sigfillset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handle_signal;
    sigaction(SIGINT, &sa, NULL);
    cout << "Press Ctrl-C to quit...." << endl;
    WeederIoTServer server;
    do
    {
        usleep(2000000);
    }
    while (quit != 1);
    return 0;

}