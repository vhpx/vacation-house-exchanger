#include <iostream>

#include "libs.h"

using namespace HouseExchanger;

int main() {
    //* Setup

    // Clear screen
    std::system("cls");

    // Get singleton system object to manage all the data
    // This is the only way to access the system object
    // and avoid system object being created multiple times
    System *system = System::getInstance();

    // By default, the system is not initialized.
    // Therefore, we have to initialize it to load all
    // data before the user can interact with the system.
    bool initialized = system->initialize();

    // Throw an exception if the system
    // failed to initialize.
    if (!initialized) {
        throw std::runtime_error("System failed to initialize correctly.");
        return 1;
    }

    // System is now initialized.
    // Display welcome message.
    displayWelcomeMsg();

    //* Main loop
    // The main loop is a while loop that runs until the user quits.
    mainLoop();

    // Shutdown the system, which will automatically
    // save all the system resources internally.
    bool shutdownSuccessful = system->shutdown();

    //* Cleanup
    delete system;

    // Throw an exception if the system
    // failed to shutdown properly.
    if (!shutdownSuccessful) {
        throw std::runtime_error("System failed to shutdown correctly.");
        return 2;
    }

    return 0;
}