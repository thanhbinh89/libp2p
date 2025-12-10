#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <fstream>
#include <variant>
#include <arpa/inet.h>
#include <signal.h>

#include "p2p_api.h"
#include "define.h"

#define LOGIN_USER "binhnt@epcb.vn"
#define LOGIN_PSK  "123456"
#define DEVICE_ID_1  "c0774560-3870-11f0-82d4-db0fa8eab971"
// #define DEVICE_ID_2  "3a1aca70-c9a0-11f0-a9ba-a19e253075c3"
using namespace std;
using namespace rtc;

bool loop_enable = true;

void sig_handler(int sig) {
    if (sig == SIGINT || sig == SIGTERM || sig == SIGQUIT) {
        fprintf(stdout, "Termination signal received, exiting...\n");
        loop_enable = false;
    }
}

void signal_handler_setup() {
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, nullptr);
    sigaction(SIGTERM, &sa, nullptr);
    sigaction(SIGQUIT, &sa, nullptr);
}

int main() {
    signal_handler_setup();

    fprintf(stdout, "Library version: %s\n", p2p_api::get_version().c_str());
    p2p_api::init();
    p2p_api::login(LOGIN_URL, LOGIN_USER, LOGIN_PSK);
    // instantiate p2p_api from shared library
    p2p_api p2p;
    p2p.start_stream(DEVICE_ID_1);
    // p2p.start_stream(DEVICE_ID_2);

    sleep(10); // wait for stream ready
    uint16_t port1 = p2p.get_port_stream(DEVICE_ID_1);
    // uint16_t port2 = p2p.get_port_stream(DEVICE_ID_2);
    fprintf(stdout, "Device %s streaming on UDP port: %d\n", DEVICE_ID_1, port1);
    // fprintf(stdout, "Device %s streaming on UDP port: %d\n", DEVICE_ID_2, port2);

    while (loop_enable) {
        sleep(1);
    }

    p2p.stop_stream(DEVICE_ID_1);
    // p2p.stop_stream(DEVICE_ID_2);
    sleep(1);

    fprintf(stdout, "\nExiting...\n");
    return 0;
}
